import pymel.core as pm
import pymel.api as api

# params: {"keyable", "hidden", "array"}, type: bool, int, float, double, vector, matrix, nurbsCurve, string
def createAttribute(node, attrName, attrType, params={}): 
    depfn = api.MFnDependencyNode(pm.PyNode(node).__apimobject__())
    
    if attrType in ["bool", "int", "float", "double", "vector"]:
        numericTypes = {"bool": api.MFnNumericData.kBoolean, 
                        "int": api.MFnNumericData.kInt, 
                        "float": api.MFnNumericData.kFloat,
                        "double": api.MFnNumericData.kDouble,
                        "vector": api.MFnNumericData.k3Double}
        
        attrfn = api.MFnNumericAttribute()
        attrObj = attrfn.create(attrName, attrName, numericTypes[attrType])

    elif attrType == "matrix":
        attrfn = api.MFnMatrixAttribute()
        attrObj = attrfn.create(attrName, attrName)

    elif attrType == "nurbsCurve":
        attrfn = api.MFnTypedAttribute()
        attrObj = attrfn.create(attrName, attrName, api.MFnData.kNurbsCurve)

    elif attrType == "string":
        attrfn = api.MFnTypedAttribute()
        attrObj = attrfn.create(attrName, attrName, api.MFnData.kString)

    elif attrType == "enum":
        attrfn = api.MFnEnumAttribute()
        attrObj = attrfn.create(attrName, attrName)
        
        items = params.get("items", [])
        for i, a in enumerate(items):
            attrfn.addField(a, i)
        
    attrfn.setArray(params.get("array", False))
    attrfn.setKeyable(params.get("keyable", False))
    attrfn.setHidden(params.get("hidden", False))
    depfn.addAttribute(attrObj)
    
    pm.select(node)
    pm.mel.eval("refreshEditorTemplates; refreshAE")

#createAttribute("rigpp1", "input", "double")
#createAttribute("rigpp1", "someMatrices", "matrix", {"array": True, "hidden": True})
#createAttribute("rigpp1", "inputCurve", "nurbsCurve")
#createAttribute("rigpp1", "indices", "int", {"array": True})
#createAttribute("rigpp1", "mode", "enum", {"items": ["One", "Two", "Three"]})
#createAttribute("rigpp1", "out_position", "vector")