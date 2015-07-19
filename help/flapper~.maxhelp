{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 7,
			"minor" : 0,
			"revision" : 3,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"rect" : [ 151.0, 154.0, 601.0, 712.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 13.0,
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
		"boxes" : [ 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-7",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "bang" ],
					"patching_rect" : [ 111.5, 305.5, 61.0, 23.0 ],
					"style" : "",
					"text" : "onebang"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-73",
					"maxclass" : "number",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 328.0, 314.0, 50.0, 23.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-71",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 328.0, 476.5, 24.0, 24.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-69",
					"maxclass" : "flonum",
					"minimum" : 0.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 328.0, 278.0, 50.0, 23.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"ft1" : 5.0,
					"id" : "obj-65",
					"maxclass" : "number~",
					"mode" : 2,
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "float" ],
					"patching_rect" : [ 23.0, 336.5, 56.0, 23.0 ],
					"sig" : 0.0,
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-64",
					"maxclass" : "newobj",
					"numinlets" : 5,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "signal" ],
					"patching_rect" : [ 23.0, 302.0, 76.0, 23.0 ],
					"style" : "",
					"text" : "findtrigger~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-61",
					"maxclass" : "newobj",
					"numinlets" : 3,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "signal" ],
					"patching_rect" : [ 23.0, 541.0, 58.0, 23.0 ],
					"style" : "",
					"text" : "flapper~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-60",
					"maxclass" : "live.gain~",
					"numinlets" : 2,
					"numoutlets" : 5,
					"orientation" : 1,
					"outlettype" : [ "signal", "signal", "", "float", "list" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 199.5, 576.04248, 136.0, 48.0 ],
					"presentation_rect" : [ 180.0, 574.04248, 50.0, 34.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.gain~[1]",
							"parameter_shortname" : "live.gain~",
							"parameter_type" : 0,
							"parameter_mmin" : -70.0,
							"parameter_mmax" : 6.0,
							"parameter_initial" : [ 0.0 ],
							"parameter_unitstyle" : 4
						}

					}
,
					"varname" : "live.gain~[1]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-3",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 246.5, 470.0, 34.0, 23.0 ],
					"style" : "",
					"text" : "poly"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-4",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 246.5, 433.04248, 42.0, 23.0 ],
					"style" : "",
					"text" : "linear"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"hidden" : 1,
					"id" : "obj-5",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 398.0, 232.0, 29.5, 23.0 ],
					"style" : "",
					"text" : "1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"hidden" : 1,
					"id" : "obj-6",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 398.0, 201.0, 64.0, 23.0 ],
					"style" : "",
					"text" : "loadbang"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-8",
					"maxclass" : "number",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 328.0, 435.0, 50.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-18",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 398.0, 435.0, 71.0, 23.0 ],
					"style" : "",
					"text" : "release $1"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"format" : 6,
					"id" : "obj-19",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 328.0, 408.0, 51.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-20",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 398.0, 408.0, 70.0, 23.0 ],
					"style" : "",
					"text" : "sustain $1"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-21",
					"maxclass" : "number",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 328.0, 381.0, 50.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-25",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 398.0, 381.0, 63.0, 23.0 ],
					"style" : "",
					"text" : "decay $1"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-26",
					"maxclass" : "number",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 328.0, 354.0, 50.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-27",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 398.0, 354.0, 63.0, 23.0 ],
					"style" : "",
					"text" : "attack $1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-29",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 210.0, 151.5, 93.0, 23.0 ],
					"style" : "",
					"text" : "open jongly.aif"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-30",
					"maxclass" : "preset",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "preset", "int", "preset", "int" ],
					"patching_rect" : [ 237.5, 278.0, 52.0, 52.0 ],
					"preset_data" : [ 						{
							"number" : 1,
							"data" : [ 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "umenu", "int", 1, 5, "obj-26", "number", "int", 20, 5, "obj-21", "number", "int", 0, 5, "obj-19", "flonum", "float", 1.0, 5, "obj-8", "number", "int", 20, 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "number~", "list", 0.0, 5, "obj-69", "flonum", "float", 1.0, 5, "obj-71", "toggle", "int", 1, 5, "obj-73", "number", "int", 1012 ]
						}
, 						{
							"number" : 2,
							"data" : [ 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "umenu", "int", 1, 5, "obj-26", "number", "int", 20, 5, "obj-21", "number", "int", 0, 5, "obj-19", "flonum", "float", 1.0, 5, "obj-8", "number", "int", 20, 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "number~", "list", 0.0, 5, "obj-69", "flonum", "float", 10.0, 5, "obj-71", "toggle", "int", 1, 5, "obj-73", "number", "int", 1000 ]
						}
, 						{
							"number" : 3,
							"data" : [ 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "umenu", "int", 1, 5, "obj-26", "number", "int", 20, 5, "obj-21", "number", "int", 0, 5, "obj-19", "flonum", "float", 1.0, 5, "obj-8", "number", "int", 20, 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "number~", "list", 0.0, 5, "obj-69", "flonum", "float", 0.5, 5, "obj-71", "toggle", "int", 1, 5, "obj-73", "number", "int", 1000 ]
						}
, 						{
							"number" : 4,
							"data" : [ 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "umenu", "int", 1, 5, "obj-26", "number", "int", 20, 5, "obj-21", "number", "int", 0, 5, "obj-19", "flonum", "float", 1.0, 5, "obj-8", "number", "int", 20, 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "number~", "list", 0.0, 5, "obj-69", "flonum", "float", 5.0, 5, "obj-71", "toggle", "int", 0, 5, "obj-73", "number", "int", 2000 ]
						}
, 						{
							"number" : 5,
							"data" : [ 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "umenu", "int", 1, 5, "obj-26", "number", "int", 20, 5, "obj-21", "number", "int", 0, 5, "obj-19", "flonum", "float", 1.0, 5, "obj-8", "number", "int", 20, 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "number~", "list", 0.0, 5, "obj-69", "flonum", "float", 50.0, 5, "obj-71", "toggle", "int", 0, 5, "obj-73", "number", "int", 2000 ]
						}
, 						{
							"number" : 6,
							"data" : [ 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "umenu", "int", 1, 5, "obj-26", "number", "int", 20, 5, "obj-21", "number", "int", 0, 5, "obj-19", "flonum", "float", 1.0, 5, "obj-8", "number", "int", 20, 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "number~", "list", 0.0, 5, "obj-69", "flonum", "float", 500.0, 5, "obj-71", "toggle", "int", 0, 5, "obj-73", "number", "int", 2000 ]
						}
, 						{
							"number" : 7,
							"data" : [ 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "umenu", "int", 1, 5, "obj-26", "number", "int", 20, 5, "obj-21", "number", "int", 0, 5, "obj-19", "flonum", "float", 1.0, 5, "obj-8", "number", "int", 20, 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "number~", "list", 0.0, 5, "obj-69", "flonum", "float", 5000.0, 5, "obj-71", "toggle", "int", 0, 5, "obj-73", "number", "int", 2000 ]
						}
, 						{
							"number" : 8,
							"data" : [ 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "umenu", "int", 1, 5, "obj-26", "number", "int", 20, 5, "obj-21", "number", "int", 0, 5, "obj-19", "flonum", "float", 1.0, 5, "obj-8", "number", "int", 20, 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "number~", "list", 0.0, 5, "obj-69", "flonum", "float", 0.25, 5, "obj-71", "toggle", "int", 0, 5, "obj-73", "number", "int", 500 ]
						}
, 						{
							"number" : 9,
							"data" : [ 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "umenu", "int", 1, 5, "obj-26", "number", "int", 300, 5, "obj-21", "number", "int", 20, 5, "obj-19", "flonum", "float", 0.1, 5, "obj-8", "number", "int", 400, 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "number~", "list", 0.0, 5, "obj-69", "flonum", "float", 10.0, 5, "obj-71", "toggle", "int", 1, 5, "obj-73", "number", "int", 1000 ]
						}
, 						{
							"number" : 10,
							"data" : [ 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "umenu", "int", 1, 5, "obj-26", "number", "int", 2300, 5, "obj-21", "number", "int", 20, 5, "obj-19", "flonum", "float", 0.1, 5, "obj-8", "number", "int", 180, 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "number~", "list", 0.0, 5, "obj-69", "flonum", "float", 2.0, 5, "obj-71", "toggle", "int", 1, 5, "obj-73", "number", "int", 2500 ]
						}
, 						{
							"number" : 11,
							"data" : [ 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "umenu", "int", 1, 5, "obj-26", "number", "int", 2300, 5, "obj-21", "number", "int", 20, 5, "obj-19", "flonum", "float", 0.1, 5, "obj-8", "number", "int", 180, 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "number~", "list", 0.0, 5, "obj-69", "flonum", "float", 0.5, 5, "obj-71", "toggle", "int", 1, 5, "obj-73", "number", "int", 2500 ]
						}
, 						{
							"number" : 12,
							"data" : [ 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "umenu", "int", 1, 5, "obj-26", "number", "int", 2300, 5, "obj-21", "number", "int", 20, 5, "obj-19", "flonum", "float", 0.1, 5, "obj-8", "number", "int", 180, 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "number~", "list", 0.0, 5, "obj-69", "flonum", "float", 50.0, 5, "obj-71", "toggle", "int", 0, 5, "obj-73", "number", "int", 2500 ]
						}
, 						{
							"number" : 13,
							"data" : [ 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "umenu", "int", 1, 5, "obj-26", "number", "int", 20, 5, "obj-21", "number", "int", 0, 5, "obj-19", "flonum", "float", 1.0, 5, "obj-8", "number", "int", 20, 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "number~", "list", 0.0, 5, "obj-69", "flonum", "float", 1.0, 5, "obj-71", "toggle", "int", 0, 5, "obj-73", "number", "int", 50 ]
						}
, 						{
							"number" : 14,
							"data" : [ 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "umenu", "int", 1, 5, "obj-26", "number", "int", 20, 5, "obj-21", "number", "int", 0, 5, "obj-19", "flonum", "float", 1.0, 5, "obj-8", "number", "int", 20, 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "number~", "list", 0.0, 5, "obj-69", "flonum", "float", 75.0, 5, "obj-71", "toggle", "int", 1, 5, "obj-73", "number", "int", 2000 ]
						}
, 						{
							"number" : 15,
							"data" : [ 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "umenu", "int", 1, 5, "obj-26", "number", "int", 20, 5, "obj-21", "number", "int", 5, 5, "obj-19", "flonum", "float", 0.1, 5, "obj-8", "number", "int", 500, 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "number~", "list", 0.0, 5, "obj-69", "flonum", "float", 1.0, 5, "obj-71", "toggle", "int", 0, 5, "obj-73", "number", "int", 600 ]
						}
, 						{
							"number" : 16,
							"data" : [ 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "umenu", "int", 1, 5, "obj-26", "number", "int", 20, 5, "obj-21", "number", "int", 5, 5, "obj-19", "flonum", "float", 0.1, 5, "obj-8", "number", "int", 500, 5, "<invalid>", "live.gain~", "float", 0.0, 5, "<invalid>", "number~", "list", 0.0, 5, "obj-69", "flonum", "float", 20.0, 5, "obj-71", "toggle", "int", 0, 5, "obj-73", "number", "int", 600 ]
						}
 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-32",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 398.0, 314.0, 69.0, 23.0 ],
					"style" : "",
					"text" : "length $1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-33",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 359.0, 477.0, 87.0, 23.0 ],
					"style" : "",
					"text" : "trigger_off $1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-36",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 128.0, 454.5, 47.0, 23.0 ],
					"style" : "",
					"text" : "$1 50"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-37",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "bang" ],
					"patching_rect" : [ 128.0, 489.0, 40.0, 23.0 ],
					"style" : "",
					"text" : "line~"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-41",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 210.0, 223.0, 119.0, 23.0 ],
					"style" : "",
					"text" : "open drumLoop.aif"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-49",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 210.0, 189.04248, 116.0, 23.0 ],
					"style" : "",
					"text" : "open isthatyou.aiff"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-52",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 454.0, 461.5, 143.0, 54.0 ],
					"style" : "",
					"text" : "have new triggers shut off older ones? (on by default)"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-53",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 478.0, 305.5, 112.0, 40.0 ],
					"style" : "",
					"text" : "length (in ms);\rmax 5000"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-54",
					"linecount" : 6,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 478.0, 354.0, 111.0, 98.0 ],
					"style" : "",
					"text" : "ADSR: attack, decay, and release times (ms), sustain level (usually between 0-1)"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-55",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 388.0, 277.0, 161.0, 25.0 ],
					"style" : "",
					"text" : "flap speed (1 = normal)"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"bubbleside" : 2,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-56",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 23.0, 143.0, 82.0, 40.0 ],
					"style" : "",
					"text" : "try an input"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"bubbleside" : 2,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-58",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 226.5, 524.0, 82.0, 40.0 ],
					"style" : "",
					"text" : "direct signal"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"bubbleside" : 2,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-59",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 224.5, 356.0, 86.0, 69.0 ],
					"style" : "",
					"text" : "interpolation type (linear is cheaper)"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-24",
					"maxclass" : "ezadc~",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "signal" ],
					"patching_rect" : [ 339.0, 201.0, 45.0, 45.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-13",
					"items" : [ "none", ",", "soundfile", ",", "adc" ],
					"labelclick" : 1,
					"maxclass" : "umenu",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "int", "", "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 23.0, 189.04248, 82.0, 23.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-14",
					"maxclass" : "newobj",
					"numinlets" : 3,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 23.0, 265.04248, 82.0, 23.0 ],
					"style" : "",
					"text" : "selector~ 2"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-9",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 179.5, 189.04248, 20.0, 23.0 ],
					"style" : "",
					"text" : "0"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-16",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 155.5, 189.04248, 20.0, 23.0 ],
					"style" : "",
					"text" : "1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-17",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 111.5, 189.04248, 40.0, 23.0 ],
					"style" : "",
					"text" : "open"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-10",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "bang" ],
					"patching_rect" : [ 111.5, 223.0, 80.0, 23.0 ],
					"saved_object_attributes" : 					{
						"basictuning" : 440,
						"followglobaltempo" : 0,
						"formantcorrection" : 0,
						"mode" : "basic",
						"originallength" : [ 2708.87619, "ticks" ],
						"originaltempo" : 120.0,
						"pitchcorrection" : 0,
						"quality" : "basic",
						"timestretch" : [ 0 ]
					}
,
					"style" : "",
					"text" : "sfplay~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-45",
					"maxclass" : "live.gain~",
					"numinlets" : 2,
					"numoutlets" : 5,
					"orientation" : 1,
					"outlettype" : [ "signal", "signal", "", "float", "list" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 23.0, 576.04248, 136.0, 48.0 ],
					"presentation_rect" : [ 0.0, 0.0, 50.0, 34.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.gain~",
							"parameter_shortname" : "live.gain~",
							"parameter_type" : 0,
							"parameter_mmin" : -70.0,
							"parameter_mmax" : 6.0,
							"parameter_initial" : [ 0.0 ],
							"parameter_unitstyle" : 4
						}

					}
,
					"varname" : "live.gain~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-2",
					"local" : 1,
					"maxclass" : "ezdac~",
					"numinlets" : 2,
					"numoutlets" : 0,
					"patching_rect" : [ 23.0, 639.04248, 45.0, 45.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-22",
					"linecount" : 5,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 8.0, 65.0, 564.0, 79.0 ],
					"style" : "",
					"text" : "• the flapper~ is a bit like scrub~, except it takes a trigger to set it going, and then scrubs (flaps) back and forth between the trigger point and, well, the \"present\" (current sample), for as long as you want it to. you can put an envelope on the duration you specify, and scrub away. the \"findtrigger~\" abstraction could easily be replaced by other things that generate zero/non-zero signals. and, obviously, the trigger signal does not need to be the same as the input signal.",
					"textcolor" : [ 0.2, 0.2, 0.2, 1.0 ],
					"varname" : "autohelp_top_digest"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 48.0,
					"id" : "obj-23",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 4.0, 3.0, 265.0, 60.0 ],
					"style" : "",
					"text" : "the flapper~",
					"textcolor" : [ 0.2, 0.2, 0.2, 1.0 ],
					"varname" : "autohelp_top_digest[1]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-1",
					"maxclass" : "fpic",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "jit_matrix" ],
					"patching_rect" : [ 454.0, 594.0, 140.0, 87.0 ],
					"pic" : "Macintosh HD:/Users/Shared/Max 7/Packages/PeRColate/media/percolate.jpg"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-15",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 258.0, 686.0, 336.0, 21.0 ],
					"style" : "",
					"text" : "• by dan trueman, music department princeton university"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 121.0, 252.0, 64.0, 252.0 ],
					"source" : [ "obj-10", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-16", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-10", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-60", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 32.5, 294.0, 209.0, 294.0 ],
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 32.5, 294.0, 104.0, 294.0, 104.0, 531.0, 52.0, 531.0 ],
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-64", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-16", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-17", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-18", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-19", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-20", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-25", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-21", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 348.5, 259.0, 95.5, 259.0 ],
					"source" : [ "obj-24", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-25", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-27", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-26", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-27", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-29", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-32", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-33", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-37", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-36", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 137.5, 534.0, 71.5, 534.0 ],
					"source" : [ "obj-37", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-41", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-45", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-45", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-49", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-4", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-6", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-5", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-6", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 1 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-6", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-60", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-60", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-45", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 71.5, 570.0, 149.5, 570.0 ],
					"source" : [ "obj-61", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-45", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-61", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 89.5, 528.0, 32.5, 528.0 ],
					"source" : [ "obj-64", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-65", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-64", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-64", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-36", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"midpoints" : [ 337.5, 307.0, 318.0, 307.0, 318.0, 343.0, 137.5, 343.0 ],
					"source" : [ "obj-69", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-73", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-7", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-71", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-32", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-73", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-9", 0 ]
				}

			}
 ],
		"parameters" : 		{
			"obj-45" : [ "live.gain~", "live.gain~", 0 ],
			"obj-60" : [ "live.gain~[1]", "live.gain~", 0 ]
		}
,
		"dependency_cache" : [ 			{
				"name" : "percolate.jpg",
				"bootpath" : "/Users/Shared/Max 7/Packages/PeRColate/media",
				"patcherrelativepath" : "../../../../../../Shared/Max 7/Packages/PeRColate/media",
				"type" : "JPEG",
				"implicit" : 1
			}
, 			{
				"name" : "findtrigger~.maxpat",
				"bootpath" : "~/Documents/Max 7/Library/PeRColate/help",
				"patcherrelativepath" : "../../PeRColate/help",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "flapper~.mxo",
				"type" : "iLaX"
			}
, 			{
				"name" : "dcblock~.mxo",
				"type" : "iLaX"
			}
 ],
		"embedsnapshot" : 0
	}

}
