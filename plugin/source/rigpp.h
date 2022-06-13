#pragma	once

#include <any>
#include <map>

#include <maya/MPxNode.h>
#include <maya/MFnPluginData.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MGlobal.h>
#include <maya/MPlug.h>

#include "jithelper.hpp"

using namespace std;

typedef enum SourceType
{
	Cpp, CppFile, LLVM_IRFile,
};

typedef enum DebugMode
{
	NoDebug,
	DebugPerfomance,
};

struct PlugMemInfo
{
	MPlug plug;
	any value;
};

class Rigpp : public MPxNode
{
public:
	~Rigpp() { mainFunction = nullptr;  }

	static MTypeId typeId;

	static MObject attr_source;
	static MObject attr_debugMode;

	static void* creator() { return new Rigpp(); }
	static MStatus initialize();
	void postConstructor();

	MStatus compute(const MPlug&, MDataBlock&);
	MStatus setDependentsDirty(const MPlug&, MPlugArray&);
	bool setInternalValue(const MPlug&, const MDataHandle&);
	void copyInternalData(MPxNode*);

	void updateSymbols();
	void getInputs(MDataBlock&);
	void setOutputs(MDataBlock&);

	bool setupJit(const string&);

private:
	MFnDependencyNode thisNodeFn;

	JITHelper jitHelper;
	map<string, PlugMemInfo> attributes; // keeps host variables
	map<string, void*> symbols; // keeps pointers for jit
	MainFunctionType* mainFunction{nullptr};
};
