//Maya ASCII 2019 scene
//Name: nurbsCurve.ma
//Last modified: Mon, Jun 13, 2022 04:58:38 PM
//Codeset: 1251
requires maya "2019";
requires -nodeType "rigpp" "rigpp" "Unknown";
requires "stereoCamera" "10.0";
currentUnit -l centimeter -a degree -t film;
fileInfo "application" "maya";
fileInfo "product" "Maya 2019";
fileInfo "version" "2019";
fileInfo "cutIdentifier" "202004141915-92acaa8c08";
fileInfo "osv" "Microsoft Windows 10 Technical Preview  (Build 19043)\n";
createNode transform -s -n "persp";
	rename -uid "78E4ED3F-4E60-5E42-3B4E-889057515538";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 8.0468842585530336 5.9701177293225687 17.310516534103684 ;
	setAttr ".r" -type "double3" -18.338352729602683 13.399999999999942 0 ;
createNode camera -s -n "perspShape" -p "persp";
	rename -uid "9BECD7B9-4A08-C326-435C-618B1DEF2436";
	setAttr -k off ".v" no;
	setAttr ".fl" 34.999999999999993;
	setAttr ".coi" 18.86321980043585;
	setAttr ".imn" -type "string" "persp";
	setAttr ".den" -type "string" "persp_depth";
	setAttr ".man" -type "string" "persp_mask";
	setAttr ".hc" -type "string" "viewSet -p %camera";
createNode transform -s -n "top";
	rename -uid "F1157874-48AE-E108-22C6-A0BABE75BDBF";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 1000.1 0 ;
	setAttr ".r" -type "double3" -90 0 0 ;
createNode camera -s -n "topShape" -p "top";
	rename -uid "7AE06560-42E8-7FC4-A6CE-B9A7079206E3";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "top";
	setAttr ".den" -type "string" "top_depth";
	setAttr ".man" -type "string" "top_mask";
	setAttr ".hc" -type "string" "viewSet -t %camera";
	setAttr ".o" yes;
createNode transform -s -n "front";
	rename -uid "55DC7F22-4B47-ACE2-0463-989D2EC70ECD";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 0 1000.1 ;
createNode camera -s -n "frontShape" -p "front";
	rename -uid "54C4C91B-425D-CC0F-C477-79A53141B1DB";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "front";
	setAttr ".den" -type "string" "front_depth";
	setAttr ".man" -type "string" "front_mask";
	setAttr ".hc" -type "string" "viewSet -f %camera";
	setAttr ".o" yes;
createNode transform -s -n "side";
	rename -uid "1C806CF8-4FBC-826B-DA49-779A51337109";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 1000.1 0 0 ;
	setAttr ".r" -type "double3" 0 90 0 ;
createNode camera -s -n "sideShape" -p "side";
	rename -uid "5EA177B2-4065-AD70-8953-1B9915CA80C2";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "side";
	setAttr ".den" -type "string" "side_depth";
	setAttr ".man" -type "string" "side_mask";
	setAttr ".hc" -type "string" "viewSet -s %camera";
	setAttr ".o" yes;
createNode transform -n "curve1";
	rename -uid "A6362203-451C-179F-0369-07B9B536AF1E";
createNode nurbsCurve -n "curveShape1" -p "curve1";
	rename -uid "41F61123-426E-8FE7-234B-86BF7F393BEB";
	setAttr -k off ".v";
	setAttr ".cc" -type "nurbsCurve" 
		3 4 0 no 3
		9 0 0 0 0.25 0.5 0.75 1 1 1
		7
		0 0 0
		0.35025053559333669 0.525375803390005 -0
		2.0286284555436715 2.3970001342505576 0
		3.7059642110993258 -0.16607567427289061 0
		5.5734634934258755 -1.6272560458300724 0
		7.4743916472352527 -0.36940197699129718 0
		8 0 0
		;
createNode transform -n "pCube1";
	rename -uid "573F4224-403A-AA75-EF2E-6EB57756A7F2";
createNode mesh -n "pCubeShape1" -p "pCube1";
	rename -uid "C02AB214-444F-4334-1609-E9BA67CCF9B1";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
createNode lightLinker -s -n "lightLinker1";
	rename -uid "BA32E932-4B62-6A24-F4F3-8EA2EEEE02C0";
	setAttr -s 2 ".lnk";
	setAttr -s 2 ".slnk";
createNode shapeEditorManager -n "shapeEditorManager";
	rename -uid "5F1B56FB-465A-8FF3-9A8E-1DBFC2614A04";
createNode poseInterpolatorManager -n "poseInterpolatorManager";
	rename -uid "5C8EBA0A-4D9D-9BED-7733-D3AE5EAD4FC3";
createNode displayLayerManager -n "layerManager";
	rename -uid "492D0122-42D0-7ADA-4A01-80A830F9C69C";
createNode displayLayer -n "defaultLayer";
	rename -uid "3FD851CD-4D7A-286C-1058-AEB2941F4155";
createNode renderLayerManager -n "renderLayerManager";
	rename -uid "7C25C5E3-426A-D9C0-5BC2-59A6403A285C";
createNode renderLayer -n "defaultRenderLayer";
	rename -uid "A25DECFF-4B8F-D4FB-5ED8-E7890E94D4A5";
	setAttr ".g" yes;
createNode rigpp -n "rigpp1";
	rename -uid "0707F95D-4A5F-7C59-D6C4-549A129A7655";
	addAttr -ci true -sn "inputCurve" -ln "inputCurve" -dt "nurbsCurve";
	addAttr -ci true -sn "param" -ln "param" -at "float";
	addAttr -ci true -sn "outPosition" -ln "outPosition" -at "double3" -nc 3;
	addAttr -ci true -sn "outPosition0" -ln "outPosition0" -at "double" -p "outPosition";
	addAttr -ci true -sn "outPosition1" -ln "outPosition1" -at "double" -p "outPosition";
	addAttr -ci true -sn "outPosition2" -ln "outPosition2" -at "double" -p "outPosition";
	setAttr "._source" -type "string" "#include <rigpp>\nextern float @param;\nextern NurbsCurve @inputCurve;\nextern Vector @outPosition;\nint main()\n{\n   @outPosition = @inputCurve.evaluate(@param); \n   return 0;\n}";
	setAttr ".param" 0.37000000476837158;
	setAttr ".outPosition" -type "double3" 2.81756407359866 1.0611776709005971 0 ;
createNode polyCube -n "polyCube1";
	rename -uid "A62F0558-4602-0D48-4D58-F59AEABA7F83";
	setAttr ".cuv" 4;
createNode script -n "sceneConfigurationScriptNode";
	rename -uid "0C7827C6-4837-097B-BB1C-1092F51EA27D";
	setAttr ".b" -type "string" "playbackOptions -min 1 -max 120 -ast 1 -aet 200 ";
	setAttr ".st" 6;
select -ne :time1;
	setAttr ".o" 1;
	setAttr ".unw" 1;
select -ne :hardwareRenderingGlobals;
	setAttr ".otfna" -type "stringArray" 22 "NURBS Curves" "NURBS Surfaces" "Polygons" "Subdiv Surface" "Particles" "Particle Instance" "Fluids" "Strokes" "Image Planes" "UI" "Lights" "Cameras" "Locators" "Joints" "IK Handles" "Deformers" "Motion Trails" "Components" "Hair Systems" "Follicles" "Misc. UI" "Ornaments"  ;
	setAttr ".otfva" -type "Int32Array" 22 0 1 1 1 1 1
		 1 1 1 0 0 0 0 0 0 0 0 0
		 0 0 0 0 ;
	setAttr ".fprt" yes;
select -ne :renderPartition;
	setAttr -s 2 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 4 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :defaultRenderingList1;
select -ne :initialShadingGroup;
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr ".ro" yes;
select -ne :defaultResolution;
	setAttr ".pa" 1;
select -ne :hardwareRenderGlobals;
	setAttr ".ctrs" 256;
	setAttr ".btrs" 512;
connectAttr "rigpp1.outPosition" "pCube1.t";
connectAttr "polyCube1.out" "pCubeShape1.i";
relationship "link" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
connectAttr "layerManager.dli[0]" "defaultLayer.id";
connectAttr "renderLayerManager.rlmi[0]" "defaultRenderLayer.rlid";
connectAttr "curveShape1.ws" "rigpp1.inputCurve";
connectAttr "defaultRenderLayer.msg" ":defaultRenderingList1.r" -na;
connectAttr "pCubeShape1.iog" ":initialShadingGroup.dsm" -na;
// End of nurbsCurve.ma
