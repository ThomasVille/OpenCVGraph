#ifndef _NODE_H_
#define _NODE_H_
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include "Parameter.h"
#include "BaseData.h"
#include "GUI\PreviewPanel.h"

// List of parameters
typedef std::unordered_map<std::string, std::shared_ptr<Parameter>> ParamList;
// The computer takes in parameter the node's inputs and outputs
typedef std::function<void(ParamList, ParamList)> ComputerType;
// The initializer takes in parameter the node's outputs
typedef std::function<void(ParamList)> InitializerType;

class Node
{
public:
	Node();
	Node(std::string name, ParamList, ParamList, InitializerType, ComputerType);
	~Node();

	ParamList GetInputs() {
		return m_inputs;
	}
	ParamList GetOutputs() {
		return m_outputs;
	}
	std::string GetName() {
		return m_name;
	}
	InitializerType GetInitializer() {
		return m_initializer;
	}
	ComputerType GetComputer() {
		return m_computer;
	}

	void SetInputs(ParamList in) {
		m_inputs = in;
	}
	void SetOutputs(ParamList out) {
		m_outputs = out;
	}
	void SetName(std::string name) {
		m_name = name;
	}
	void SetInitializer(InitializerType initializer) {
		m_initializer = initializer;
	}
	void SetComputer(ComputerType computer) {
		m_computer = computer;
	}

	void AddOutputLink(std::string sourceParam, std::shared_ptr<Parameter> dstParam) {
		// First check if the sourceParam exists
		if (m_outputs.find(sourceParam) == m_outputs.end())
			return;
		// Then add the link
		m_outputs[sourceParam]->AddLink(dstParam);
	}
	void AddInputLink(std::string dstParam, std::shared_ptr<Parameter> srcParam) {
		if (m_inputs.find(dstParam) == m_inputs.end())
			return;
		m_inputs[dstParam]->AddLink(srcParam);
	}
private:
	ParamList m_inputs;
	ParamList m_outputs;
	ComputerType m_computer;
	InitializerType m_initializer;
	std::string m_name;
};



#endif // !_NODE_H_