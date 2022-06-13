//Maya ASCII 2019 scene
//Name: matrix.ma
//Last modified: Mon, Jun 13, 2022 05:29:47 PM
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
	rename -uid "FF12FC94-46C7-6B21-2751-78B59D51EBAE";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 10.42947992394673 12.471592448388316 5.9869428573711527 ;
	setAttr ".r" -type "double3" -44.738352729604664 49.000000000001357 4.8479702906575263e-15 ;
createNode camera -s -n "perspShape" -p "persp";
	rename -uid "81C274E8-48D5-E291-36B6-47ACB7283E9A";
	setAttr -k off ".v" no;
	setAttr ".fl" 34.999999999999993;
	setAttr ".coi" 17.123007740082372;
	setAttr ".imn" -type "string" "persp";
	setAttr ".den" -type "string" "persp_depth";
	setAttr ".man" -type "string" "persp_mask";
	setAttr ".hc" -type "string" "viewSet -p %camera";
createNode transform -s -n "top";
	rename -uid "9A4BF7B8-4A34-9FAF-9E78-7299FDA92FEC";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 1000.1 0 ;
	setAttr ".r" -type "double3" -90 0 0 ;
createNode camera -s -n "topShape" -p "top";
	rename -uid "48CDF5AC-403F-6417-EE39-D6A252F7A016";
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
	rename -uid "E0A29CBD-4342-57AD-84BE-C38014C8A8F1";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 0 1000.1 ;
createNode camera -s -n "frontShape" -p "front";
	rename -uid "29261FAC-411C-FC5A-1E3C-8482A7A6E774";
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
	rename -uid "E1836381-4907-C0AC-B7E9-90A8BB9B90B9";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 1000.1 0 0 ;
	setAttr ".r" -type "double3" 0 90 0 ;
createNode camera -s -n "sideShape" -p "side";
	rename -uid "851A9660-4E67-89AA-CF2A-F7AEF988EB32";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "side";
	setAttr ".den" -type "string" "side_depth";
	setAttr ".man" -type "string" "side_mask";
	setAttr ".hc" -type "string" "viewSet -s %camera";
	setAttr ".o" yes;
createNode transform -n "a";
	rename -uid "FA8890FB-4D6A-9BAF-0BA3-FBA4E4DA9C22";
	setAttr ".t" -type "double3" 0 0 -2.3683674192359914 ;
	setAttr ".r" -type "double3" 34.302558659919825 28.743505622246303 54.820378891631194 ;
	setAttr ".dla" yes;
createNode mesh -n "aShape" -p "a";
	rename -uid "BB94F41E-4C23-0B36-AF1A-19A172BD4AFB";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr -s 14 ".uvst[0].uvsp[0:13]" -type "float2" 0.375 0 0.625 0 0.375
		 0.25 0.625 0.25 0.375 0.5 0.625 0.5 0.375 0.75 0.625 0.75 0.375 1 0.625 1 0.875 0
		 0.875 0.25 0.125 0 0.125 0.25;
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 8 ".vt[0:7]"  -0.5 -0.5 0.5 0.5 -0.5 0.5 -0.5 0.5 0.5 0.5 0.5 0.5
		 -0.5 0.5 -0.5 0.5 0.5 -0.5 -0.5 -0.5 -0.5 0.5 -0.5 -0.5;
	setAttr -s 12 ".ed[0:11]"  0 1 0 2 3 0 4 5 0 6 7 0 0 2 0 1 3 0 2 4 0
		 3 5 0 4 6 0 5 7 0 6 0 0 7 1 0;
	setAttr -s 6 -ch 24 ".fc[0:5]" -type "polyFaces" 
		f 4 0 5 -2 -5
		mu 0 4 0 1 3 2
		f 4 1 7 -3 -7
		mu 0 4 2 3 5 4
		f 4 2 9 -4 -9
		mu 0 4 4 5 7 6
		f 4 3 11 -1 -11
		mu 0 4 6 7 9 8
		f 4 -12 -10 -8 -6
		mu 0 4 1 10 11 3
		f 4 10 4 6 8
		mu 0 4 12 0 2 13;
	setAttr ".cd" -type "dataPolyComponent" Index_Data Edge 0 ;
	setAttr ".cvd" -type "dataPolyComponent" Index_Data Vertex 0 ;
	setAttr ".pd[0]" -type "dataPolyComponent" Index_Data UV 0 ;
	setAttr ".hfd" -type "dataPolyComponent" Index_Data Face 0 ;
createNode transform -n "b";
	rename -uid "4EE8739E-4948-9473-2742-6CA78C2881DF";
	setAttr ".t" -type "double3" 0 0 1.5077162370970045 ;
	setAttr ".dla" yes;
createNode mesh -n "bShape" -p "b";
	rename -uid "E42F328B-4D65-E306-9524-DB9172B93C2C";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr -s 14 ".uvst[0].uvsp[0:13]" -type "float2" 0.375 0 0.625 0 0.375
		 0.25 0.625 0.25 0.375 0.5 0.625 0.5 0.375 0.75 0.625 0.75 0.375 1 0.625 1 0.875 0
		 0.875 0.25 0.125 0 0.125 0.25;
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 8 ".vt[0:7]"  -0.5 -0.5 0.5 0.5 -0.5 0.5 -0.5 0.5 0.5 0.5 0.5 0.5
		 -0.5 0.5 -0.5 0.5 0.5 -0.5 -0.5 -0.5 -0.5 0.5 -0.5 -0.5;
	setAttr -s 12 ".ed[0:11]"  0 1 0 2 3 0 4 5 0 6 7 0 0 2 0 1 3 0 2 4 0
		 3 5 0 4 6 0 5 7 0 6 0 0 7 1 0;
	setAttr -s 6 -ch 24 ".fc[0:5]" -type "polyFaces" 
		f 4 0 5 -2 -5
		mu 0 4 0 1 3 2
		f 4 1 7 -3 -7
		mu 0 4 2 3 5 4
		f 4 2 9 -4 -9
		mu 0 4 4 5 7 6
		f 4 3 11 -1 -11
		mu 0 4 6 7 9 8
		f 4 -12 -10 -8 -6
		mu 0 4 1 10 11 3
		f 4 10 4 6 8
		mu 0 4 12 0 2 13;
	setAttr ".cd" -type "dataPolyComponent" Index_Data Edge 0 ;
	setAttr ".cvd" -type "dataPolyComponent" Index_Data Vertex 0 ;
	setAttr ".pd[0]" -type "dataPolyComponent" Index_Data UV 0 ;
	setAttr ".hfd" -type "dataPolyComponent" Index_Data Face 0 ;
createNode transform -n "out";
	rename -uid "734FAC31-4EFF-83DF-A573-F68C7ED7D033";
	setAttr ".dla" yes;
createNode mesh -n "outShape" -p "out";
	rename -uid "EF42C6B5-4E88-C54D-7596-7DB40E4ED5A8";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr -s 14 ".uvst[0].uvsp[0:13]" -type "float2" 0.375 0 0.625 0 0.375
		 0.25 0.625 0.25 0.375 0.5 0.625 0.5 0.375 0.75 0.625 0.75 0.375 1 0.625 1 0.875 0
		 0.875 0.25 0.125 0 0.125 0.25;
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 8 ".vt[0:7]"  -0.5 -0.5 0.5 0.5 -0.5 0.5 -0.5 0.5 0.5 0.5 0.5 0.5
		 -0.5 0.5 -0.5 0.5 0.5 -0.5 -0.5 -0.5 -0.5 0.5 -0.5 -0.5;
	setAttr -s 12 ".ed[0:11]"  0 1 0 2 3 0 4 5 0 6 7 0 0 2 0 1 3 0 2 4 0
		 3 5 0 4 6 0 5 7 0 6 0 0 7 1 0;
	setAttr -s 6 -ch 24 ".fc[0:5]" -type "polyFaces" 
		f 4 0 5 -2 -5
		mu 0 4 0 1 3 2
		f 4 1 7 -3 -7
		mu 0 4 2 3 5 4
		f 4 2 9 -4 -9
		mu 0 4 4 5 7 6
		f 4 3 11 -1 -11
		mu 0 4 6 7 9 8
		f 4 -12 -10 -8 -6
		mu 0 4 1 10 11 3
		f 4 10 4 6 8
		mu 0 4 12 0 2 13;
	setAttr ".cd" -type "dataPolyComponent" Index_Data Edge 0 ;
	setAttr ".cvd" -type "dataPolyComponent" Index_Data Vertex 0 ;
	setAttr ".pd[0]" -type "dataPolyComponent" Index_Data UV 0 ;
	setAttr ".hfd" -type "dataPolyComponent" Index_Data Face 0 ;
createNode lightLinker -s -n "lightLinker1";
	rename -uid "D3285B31-44F7-89FA-B69D-1BBEAE0FE7FC";
	setAttr -s 2 ".lnk";
	setAttr -s 2 ".slnk";
createNode shapeEditorManager -n "shapeEditorManager";
	rename -uid "2ED29371-4E63-C9C3-72DE-849F99731CD1";
createNode poseInterpolatorManager -n "poseInterpolatorManager";
	rename -uid "9E728D7F-4064-974D-48B0-FEB4FEFC0B2A";
createNode displayLayerManager -n "layerManager";
	rename -uid "38B46227-4A67-5FF1-5CF2-D88AA89B4BE2";
createNode displayLayer -n "defaultLayer";
	rename -uid "53999F20-4B28-A17D-424F-E5A95A5C91F6";
createNode renderLayerManager -n "renderLayerManager";
	rename -uid "60C9FA66-4F55-C027-50BB-788E182C587B";
createNode renderLayer -n "defaultRenderLayer";
	rename -uid "0DBD33D2-4AC8-6FF3-EF4F-8EAC9C0AD5CB";
	setAttr ".g" yes;
createNode rigpp -n "rigpp1";
	rename -uid "BE86CE48-4D3C-8181-E387-2B92F11E8DD6";
	addAttr -ci true -sn "a" -ln "a" -at "matrix";
	addAttr -ci true -sn "b" -ln "b" -at "matrix";
	addAttr -ci true -sn "outTranslate" -ln "outTranslate" -at "double3" -nc 3;
	addAttr -ci true -sn "outTranslate0" -ln "outTranslate0" -at "double" -p "outTranslate";
	addAttr -ci true -sn "outTranslate1" -ln "outTranslate1" -at "double" -p "outTranslate";
	addAttr -ci true -sn "outTranslate2" -ln "outTranslate2" -at "double" -p "outTranslate";
	addAttr -ci true -sn "outRotate" -ln "outRotate" -at "double3" -nc 3;
	addAttr -ci true -sn "outRotate0" -ln "outRotate0" -at "double" -p "outRotate";
	addAttr -ci true -sn "outRotate1" -ln "outRotate1" -at "double" -p "outRotate";
	addAttr -ci true -sn "outRotate2" -ln "outRotate2" -at "double" -p "outRotate";
	addAttr -ci true -sn "weight" -ln "weight" -at "float";
	setAttr "._source" -type "string" "#include <rigpp>\nextern float @weight;\nextern Matrix @a;\nextern Matrix @b;\nextern Vector @outTranslate;\nextern Vector @outRotate;\nint main()\n{\n   Matrix m = @a.blend(@b, @weight);\n   @outTranslate = m.translation();\n   @outRotate = m.eulerRotation();\n   return 0;\n}";
	setAttr ".outTranslate" -type "double3" 0 0 -0.43032559106949342 ;
	setAttr ".outRotate" -type "double3" 11.87787529306552 17.091056679590878 22.15323048851214 ;
	setAttr ".weight" 0.5;
createNode unitConversion -n "unitConversion1";
	rename -uid "25F0DE53-420A-8A43-1264-868704588C1E";
	setAttr ".cf" 0.017453292519943295;
createNode script -n "sceneConfigurationScriptNode";
	rename -uid "6908667B-4C1A-91F6-7669-DEA358C383EA";
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
	setAttr -s 3 ".dsm";
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr ".ro" yes;
select -ne :defaultResolution;
	setAttr ".pa" 1;
select -ne :hardwareRenderGlobals;
	setAttr ".ctrs" 256;
	setAttr ".btrs" 512;
connectAttr "rigpp1.outTranslate" "out.t";
connectAttr "unitConversion1.o" "out.r";
relationship "link" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
connectAttr "layerManager.dli[0]" "defaultLayer.id";
connectAttr "renderLayerManager.rlmi[0]" "defaultRenderLayer.rlid";
connectAttr "a.m" "rigpp1.a";
connectAttr "b.m" "rigpp1.b";
connectAttr "rigpp1.outRotate" "unitConversion1.i";
connectAttr "defaultRenderLayer.msg" ":defaultRenderingList1.r" -na;
connectAttr "aShape.iog" ":initialShadingGroup.dsm" -na;
connectAttr "bShape.iog" ":initialShadingGroup.dsm" -na;
connectAttr "outShape.iog" ":initialShadingGroup.dsm" -na;
// End of matrix.ma
