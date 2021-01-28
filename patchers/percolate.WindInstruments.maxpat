{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 8,
			"minor" : 2,
			"revision" : 0,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"classnamespace" : "box",
		"rect" : [ 40.0, 82.0, 277.0, 346.0 ],
		"bglocked" : 0,
		"openinpresentation" : 1,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 1,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 1,
		"objectsnaponopen" : 1,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"lefttoolbarpinned" : 0,
		"toptoolbarpinned" : 0,
		"righttoolbarpinned" : 0,
		"bottomtoolbarpinned" : 0,
		"toolbars_unpinned_last_save" : 0,
		"tallnewobj" : 0,
		"boxanimatetime" : 200,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"style" : "",
		"subpatcher_template" : "",
		"assistshowspatchername" : 0,
		"boxes" : [ 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-13",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 417.5, 227.797086074942627, 100.0, 35.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 109.20000034570694, 206.899114630425231, 123.0, 21.0 ],
					"text" : "One tonehole clarinet"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-12",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 428.5, 371.40000194311142, 100.0, 35.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 109.20000034570694, 268.499981372399475, 134.0, 21.0 ],
					"text" : "A police/referee whistle"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-11",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 369.5, 258.40000194311142, 100.0, 21.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 109.20000034570694, 145.298247888451044, 91.0, 21.0 ],
					"text" : "A saxophone"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-8",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 232.5, 300.40000194311142, 100.0, 21.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 109.20000034570694, 299.300414743386568, 91.0, 21.0 ],
					"text" : "A blown bottle"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-6",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 98.5, 189.40000194311142, 100.0, 35.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 109.20000034570694, 114.497814517463951, 102.0, 21.0 ],
					"text" : "Brass instruments"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-3",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 98.5, 213.40000194311142, 100.0, 21.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 109.20000034570694, 176.098681259438138, 78.0, 21.0 ],
					"text" : "A clarinet"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-2",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 102.5, 342.40000194311142, 100.0, 21.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 109.20000034570694, 237.699548001412325, 78.0, 21.0 ],
					"text" : "A flute"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-5",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 16.5, 435.0, 51.0, 22.0 ],
					"text" : "pcontrol"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-7",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 16.5, 405.0, 48.0, 22.0 ],
					"text" : "help $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-9",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 16.5, 374.0, 94.0, 22.0 ],
					"text" : "prepend symbol"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-32",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 16.5, 303.717647052512234, 64.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 19.600003957748413, 267.768036978406599, 70.19999623298645, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "whistle~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-42",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 16.5, 223.811766133588719, 80.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 19.800000190734863, 206.459947994029505, 70.0, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "blow_hole~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-44",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 16.5, 196.447060111690803, 78.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 19.600003957748413, 298.422081470595174, 70.19999623298645, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "blow_botl~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-38",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 16.5, 258.541178177384552, 74.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 19.600003957748413, 145.151859009652469, 70.19999623298645, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "saxofony~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-180",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 16.5, 167.623530002201221, 44.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 19.800000190734863, 237.113992486218081, 70.0, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "flute~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-181",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 16.5, 140.258823980303305, 40.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 19.800000190734863, 175.805903501840987, 70.0, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "clar~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-182",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 16.5, 112.894117958405388, 50.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 19.800000190734863, 114.497814517463951, 70.0, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "brass~"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Futura",
					"fontsize" : 18.0,
					"id" : "obj-1",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 7.5, 67.0, 149.0, 30.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 7.5, 67.0, 149.0, 30.0 ],
					"text" : "Wind Instruments"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 1,
					"fontname" : "Futura Bold",
					"fontsize" : 36.0,
					"id" : "obj-4",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 7.5, 12.0, 203.0, 53.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 7.5, 12.0, 203.0, 53.0 ],
					"text" : "PeRColate"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-180", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-181", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-182", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-32", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-38", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-42", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-44", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-5", 0 ],
					"source" : [ "obj-7", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"source" : [ "obj-9", 0 ]
				}

			}
 ],
		"dependency_cache" : [  ],
		"autosave" : 0,
		"styles" : [ 			{
				"name" : "Audiomix",
				"default" : 				{
					"bgfillcolor" : 					{
						"type" : "gradient",
						"color1" : [ 0.376471, 0.384314, 0.4, 1.0 ],
						"color2" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
						"color" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
						"angle" : 270.0,
						"proportion" : 0.39
					}

				}
,
				"parentstyle" : "",
				"multi" : 0
			}
, 			{
				"name" : "Max 12 Regular",
				"parentstyle" : "",
				"multi" : 0
			}
 ]
	}

}
