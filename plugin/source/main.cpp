#include <maya/MFnPlugin.h>

#include "rigpp.h"

MStatus initializePlugin(MObject plugin)
{
	const char *rigpp_runtimeEnv = getenv("RIGPP_RUNTIME");
	if (rigpp_runtimeEnv==nullptr)
	{
		MGlobal::displayError("RIGPP_RUNTIME environment variable must be set");
		return MS::kSuccess;
	}

	JITHelper::ROOT_PATH = rigpp_runtimeEnv;

	JITHelper::initLLVM();

	MFnPlugin pluginFn(plugin);
	MStatus stat;

	stat = pluginFn.registerNode("rigpp", Rigpp::typeId, Rigpp::creator, Rigpp::initialize);
	CHECK_MSTATUS_AND_RETURN_IT(stat);

	return MS::kSuccess;
}

MStatus uninitializePlugin(MObject plugin)
{
	JITHelper::shutdownLLVM();

	MFnPlugin pluginFn(plugin);
	MStatus stat;

	stat = pluginFn.deregisterNode(Rigpp::typeId);
	CHECK_MSTATUS_AND_RETURN_IT(stat);

	stat = pluginFn.deregisterCommand("rigpp");
	CHECK_MSTATUS_AND_RETURN_IT(stat);

	return MS::kSuccess;
}
