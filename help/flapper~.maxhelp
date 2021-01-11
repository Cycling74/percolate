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
		"rect" : [ 163.0, 122.0, 601.0, 712.0 ],
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
		"assistshowspatchername" : 0,
		"boxes" : [ 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-7",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "bang" ],
					"patching_rect" : [ 111.5, 305.5, 61.0, 23.0 ],
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
					"patching_rect" : [ 328.0, 314.0, 50.0, 23.0 ]
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
					"patching_rect" : [ 328.0, 476.5, 24.0, 24.0 ]
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
					"patching_rect" : [ 328.0, 278.0, 50.0, 23.0 ]
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
					"sig" : 0.0
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
					"text" : "flapper~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-60",
					"lastchannelcount" : 0,
					"maxclass" : "live.gain~",
					"numinlets" : 2,
					"numoutlets" : 5,
					"orientation" : 1,
					"outlettype" : [ "signal", "signal", "", "float", "list" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 199.5, 576.042479999999955, 136.0, 47.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_initial" : [ 0.0 ],
							"parameter_longname" : "live.gain~[1]",
							"parameter_mmax" : 6.0,
							"parameter_mmin" : -70.0,
							"parameter_shortname" : "live.gain~",
							"parameter_type" : 0,
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
					"patching_rect" : [ 246.5, 433.042480000000012, 42.0, 23.0 ],
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
 ]
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
					"patching_rect" : [ 210.0, 189.042480000000012, 116.0, 23.0 ],
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
					"patching_rect" : [ 339.0, 201.0, 45.0, 45.0 ]
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
					"patching_rect" : [ 23.0, 189.042480000000012, 82.0, 23.0 ]
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
					"patching_rect" : [ 23.0, 265.042480000000012, 82.0, 23.0 ],
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
					"patching_rect" : [ 179.5, 189.042480000000012, 20.0, 23.0 ],
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
					"patching_rect" : [ 155.5, 189.042480000000012, 20.0, 23.0 ],
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
					"patching_rect" : [ 111.5, 189.042480000000012, 40.0, 23.0 ],
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
						"originallength" : [ 2708.876189999999951, "ticks" ],
						"originaltempo" : 120.0,
						"pitchcorrection" : 0,
						"quality" : "basic",
						"timestretch" : [ 0 ]
					}
,
					"text" : "sfplay~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-45",
					"lastchannelcount" : 0,
					"maxclass" : "live.gain~",
					"numinlets" : 2,
					"numoutlets" : 5,
					"orientation" : 1,
					"outlettype" : [ "signal", "signal", "", "float", "list" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 23.0, 576.042479999999955, 136.0, 47.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_initial" : [ 0.0 ],
							"parameter_longname" : "live.gain~",
							"parameter_mmax" : 6.0,
							"parameter_mmin" : -70.0,
							"parameter_shortname" : "live.gain~",
							"parameter_type" : 0,
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
					"patching_rect" : [ 23.0, 639.042479999999955, 45.0, 45.0 ]
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
					"text" : "the flapper~",
					"textcolor" : [ 0.2, 0.2, 0.2, 1.0 ],
					"varname" : "autohelp_top_digest[1]"
				}

			}
, 			{
				"box" : 				{
					"data" : [ 21701, "png", "IBkSG0fBZn....PCIgDQRA...PH...vRHX....Pr5+hw....DLmPIQEBHf.B7g.YHB..f.PRDEDU3wIq7lGkuccUeme1my4N8anldySROMXYIaIaYMXabKBN1AaBDyPLNwPiYQ28pI.INrLPSXYRhgDRXk.c2D2jAZLtoooS2MIPGvMXLFVDHFrsjikwRVxR5ogmdyUUupdU8a5NbNmc+GmaUumLYsjBj6ZUq58p5W8628dN6yd+c+c+cuklFUUUQUHFgXLR5+q.fOJnpPLFI3iDi.XPDChHz3izz1QHnHFKXb3iPmOfpBlnI893U57gzeqUHFgllP5uAPiPLp36.uGBAPUHqB7AXwhNZ8AbYEo+Ve.TCwP5dKFgnlt2TRuWppnhfyHz0pz1.Xf4MWiwKsByW.MKROm687u2226pqSQDAQX+WWH.gPjXLhw3v2oz0Anf0BJ82+Dwa.uuEiIiXvRcMjIfK8XSs85q6gPfXn+Cte8UaTZZav21gfEmXR2ewz8kwBpF.h.J9PKssMnZ.q0hDB822AhQOgXGnATMBDQMBAeGM0yoJOGmueiGATCHFS5Ip+mmoR+hfAAkXTeIKXYNCp5H5fnZvGUPiX.vJDCo2GqEPr38Q55h.FJJrz1kVP1yXKFELFRa.Z51PTvXLXLJhj9cVDhFEKRxHPCHZZS.cuMPAAHDBXrFJJffBgYJKlGnqyx.qlNDfRThnHouGETUwHEW2Xn2fQhfQMnHPrAi3vXD7co8EmUvJJdeCQSEFoj11FrFHO2RHDXZ6LxxLTDGkVeUCQLDf90+zdRLSIFMHpAQAgHRxtGqH3ognFABHISQPBnj17sz0u+FQLdLDHFSFDJoCUhUIKGLYfS0qeBvXj82n09MCe+6mw.lbAMJ6+6AvGTLVKw.3i.cPHn3bIK7fM8ZfzBkpF79VTArVKFeZEPEEwHX6uEhgjghODAwfUfLqAwj1nDAbhAwABfpl88rIBHXHhh0Hz1AgPWZgUrLd3pTUl9L55LDBFBAEipICRUIDBDBJfmnp.FhjLXzjEAnBymojmaw4RdkZaSdprVAisBM.UNH5ywYDhZxnvXFiyJD65WKiPLD6M55WbUAwXvJkDkbhphFhDhoCIpwf0Y6OwqXL.hGmlSH32yGGxdVzDwDCnw.RziFiDh6f0XQxJAmC2dm3LFAS++VUH16YvXSt4YOGItdik3dFMBhprmSC0J.N7wTXn7rdCqX.TKNKHk4oE6nlV3LBVW5rN.AOzpJAexcmwp3rIOAhPxMWuWDo26ipR+AAoeCTwfPnMsYlkIzF7XTKNfl4PS8Djxw3CPHH6ajqpPPc3iQb4lqGFIlhGH8mfEfLUQQAiPlKc.PUk.ovJlXKYlJpbo62Iy7TT3HGgtZf790Qo26b35dFAHK4LEiyPHDIfAHfFSavwne+MeQrHXwXBDioCHQsi9WbxvP.QTDIYEJQGQ0hBzFb3rNy9tg22Pp2hETJKrIWZ8VtoX8oStgfRlI86UTLhPVFXcBscBsscf3HOWvzYvGhnXHyIXrBcsArhlN0sma9dWkFArljSPwHoicFAw1GG2v9FPX.0BfPzjB6DiJAMBZfLqi7JC1fM4wqFjPGG8vJarcG1X.hgzBpHHhkfFHXCDCUIuNwX5T49VMIOfUUBSlFH1Ew4bTY26yGZ5BjOnhISRdmNxAsXkY36pAyPZagb6nzY2Xr+fXjX75dpigHY83fhDoUCXz.AMPTgLiCi0fpR5jtHXQvIN.nt8Z6eOKH83NLDEKFQvZCzDBHXvSDWOltqu3t2+QhIiDiPLb8EBw.F.STP0HhnXEHhRPTbxdf5ffQHD73bNbVC0MAZ8cn3vJFvIz4Uhw.gnhFSaFwnf0.RdxUNBDMfQSFcw93moioljmFS+sd7k9fjWjQWPoM.gnmPHGSDNzZ47N9ZGxAVI8bEIlVvvd8Miux0E12Q4M7yawqco0DIRPCIbGjATxG4WsgKbtMX3.g2463l3UcyGkH6PFkXjBLTmrn2+y8k9INQs8+9z8SDHnQ7dOMcd5pSXRznhwX.LIvoZxivYd1Q2P3OvXRdQ1K75rMxX24JcJ3Abuj0ua7wtGOwdno0dD7FiAqsOLSvhIH8uTCpOru6OmAhYVfv9ggbtjarfFAQvkkhKmNY1CpLDwXrD62Z1y4PHjNgHFKFcObCZOJ68BejvCkLN5wEE5P0Tl.pMgunsC5ZWmUW4jjs+owqGV7kbYBuDuB68Z2yaZLZwIkjNXoDiVLlBPg5ZkW7YU14ZGisCy34d7.u1SaQnfLBXT.J+SascCWKjD.88vYFAhhAw3HhmnOCBtTHs9Lf79DNKqwwvrHc.s8dzkfYerhpBGdMPLdVnNBB3RAs9JuttUpyZHrWPyazjo2ByX5c0KBgfgVum8P5k6DDb2PZoNxy6SSKF.r3bFvAZz7RR6T0T1LVSxZZOz0l89RRYLXAh6Gq4F1G626LhfKJDkDHr7JAaqhuaWDlAlpa3gxvW4kJwdPYW2X3k74fEUs6uYr2sxrYJO0ScNtvkNDqMVXxTgy7zWj1Y2LKMzAAEM.3ZSq3hM8Pci2CJjoFTI8z4SmivIPDg.YrnQIFR3thZJM4tV.rXLJUkoCHZLcfgaHIBUAS.zfGQSfxLokzuxu1eYmNfnwfjYQxLXcIuzIfnJK7dpCJRFTNxPQUFQsCMDHyciFOobkCpRGIrDFmfJI.o48oDtnsESFXxDBZf5XGQiPdkipQNTABIDdHnTGC3UOhEbYBVaBsezCDg19b0GjEHKlSWTwm2gwcaXY3K4YMEp7k9Ux0u6FdcuzKuoGqoRxakIh23wTBG8lOLG5lZnMClapXkCmgwDg.DahH4sfOG5lCLCBFz.nRMQwSSmxPyLFH03jNBw.sdEEvIBkNGhokXumxPDZ7PThf0CR.w2vfBnJOk5pJF7.MZKgLOsQX0UKYTgmSrh7ehmvWgW6kJSUkCqUnqSw6AmCppxw5DZZ7TV.kE4jmki01CpoeS55FKJ9vdFYl844PLrOHGU084zvXLIbINCE4VbVaJEpdBifHVGjks28Z59cevulq6x+OuWFliPKpoiPnEiDwBTjor1JFdS2+PVYbf631L7PukixfJaBzbYAdMOAZtHCjxaHzmAk4Xc.5PT0gEKkYBEY8t6kVb40zzNGeXA8Ymiw.9fkf2fFsIxoDHKSnnnOKMU6I0ChVE0BhyCtjo+q3q84vR166BNqPHnnwTN5YYFJyAQsD8ArNgrnBRhqhDXBSOqhoGf8xhwZExxsD7w82zAHFRowkhkK6igQECM8wNMhfwAFI8PmhkBrOFE4Ft+k+TfE+y5kv.TZQHf0YPvQzm.UWZyYYoC+zETTkm71n.3QMN5HjHphgzTqTje80ChFb1cP8qf0lvK3iyIfPTDhDvgvgO9Zrw5sb0M2l1FCkkKQdep7deJUVUg7bHDEZCJDAiwQPUbYoCHYpES9+YZP7RVHjzo8l1.hXvkYH3UBInAXsPQQF9Nc+X9QIhwJ3XOfhJ19zCZaCj4rHhg4QehYS1Cvnf1EQSIlPn2CRDvzkRUylRvFwAwdONgXDwtGym84yB6yD5+ovP9etWZ.DaNQE19pQ1Z8.wnxfhHiGaoaxBtiSURVgi5cUt1VAzPFarSfMmrfSbpAbzCYvVpDogHAxjJfbZmpjW0GNR7XECNYDAE5jzyeVNLXbFgvpbsslQ1M.Ew2EvoIB3RzArG07JVIkpeWP5MBKv6kWoFD+oAssmaXCwD6hVg1PrmVzDISNiPSWW+qOY01yGBgXfXHhXy5I3JYIk.Cp6+YX6yxfLCl.D5csj3CIPtyBcFZ8AHpDHAN0zSCuJrOt4aLSj+K0kX2AkkYqsi7negITOKv8d2KyoNUNhsg+xecFTynDfv.TZfs2LxS+jM7DO+DLYWg2621svAV0fgxD0xrKQxIqX.A.ut.CQxjATGfOyizwW9YlyFasfACib5aZD268LhUWthYS6XVM3JbHFOhTrOQWIiAOdehqDeLkIjyJDhfQz+r4gXeRrLBVqquVGw8Q1Co38gPf7LS5CSSrgFhBgXOcbDSbp2yrnODQDCFQw68ITuhEiEbAHrG4SwDHUgDQYFQIykRUU6MXBplLJyLoBMES0y.qkPWed5+4zX.fHUb1KrCascNtAQN5ACbfSXPx7nMc3JETlmn92jrLW4.4bOuA3.27pbtKb.9E+nmgwKsfu4uk6jAkMTksLCKDZkYXLCInRhqCYH6NIxW3K1xW5LBWa5XrxkooQ3M75FwfgVZaZAMinUHfAi1ycQXurfDhw.MMfOZIzRJKOMkEyqXCh8he+UdYLoJYpph0Z6Q4u2u0Rdtg1VMgQPDrphJVLdCEEYLuMfFMjkkQn2fHKKi55VLlzal1C1jD.8T5mFCPjPS5DetSREmKHDTvqw8qofuuBYld9e7sIuX+WhqtPNO1icMZ8UbpSOl0NjA0EIFbHlQDWnzpP9f.PCDqQbAt4SsDG8TFFLJPU1sPm2ygNXAKZDdjGYNFx4AdvA3J.iTRPUl0E3EunxS8bWlcVbbTGTu3Xb9KbY1YWkgE0f5IKqfNEhZFgPuAQLPTSXzL0oD.7QvJIx9DCzEi+Y.T49.JSIg48IVvDQvZkd2SoZTTTjbY68JQUw5RrInpRzk39uSsI9FrJMMo3e44BssfyZIFBHHobw2OpUDqQvXr35AjFH888Jgs0ZwYRdkRk585UJ8FKu+edul2nbtyY44d9HO7CGY7xWk23854M7ZNLG9.UXJDJM0oJADFhFFh1n7veAOOwysfm+bVlUuE21s2xhlaFWVNu4GJGe.9rO7kHDcbOutCxxib3bVxxCnFOjEXdskJmPHlw3wBiGTQW8LlOCp8fq.ZZ5.qfO3QEGYYVxbNDIQXnn0H3vHFTsAo9kYkwvDLLNAjS1MQsreXhZYIApSx6nQqYtNf5VCWciH1HDaqIZJ22uRLBZu6981TzPFKpASdjPrghxLrVAalic2cAkEUXsP8hjuOemhSDZaBT3rr0rFr1LTDlNeAUCpX1hDioUUV1YWkNMRzaHCnQ7DvQVSC+2+sMNUeBoAg.ZX.nPjEXcEnZMBlD0qldhIhZhTSe.wJzHNhpm465Q6FPyTky+7ynvTQ6hHKcmQp6x4K8E87W6cWPT2gG8IGxKb1HsSaPljy0pgytdfSeqav66a6lXnQRgBcPTp4+kObjSbGNdn2YKSBC4S7uqiG9S0QnwPc0TdiO3BduumSwXqvW3yMGmIGryoXTC6r0HDwgQDlMKIM.iAVrvSVlis1Rw6SdIBgWAXH55xw0GFHDFPYgCiKxj46hyVQkZI5yvSFW9xA9s+seBtqW8cvMeJCH6vRCp1O+ZmcO9.Ln8wUJJVjNQmUQaaEKZLrwlKH1YISS4l20oTWWmXELpXLYz00RHXHOOGHIhFiwPSSruD3F55fttNL4VrYf1AwfGWgirns+uyiyUfuCbYQhrMltC.zBTQ2dKThf26Sdkvf5tdsE73XvxfRKCNPNG3lVhLCH5kXg+X767I2ha61sXzBd7uvP9j+t6hWx4jGMiUJEFHJG+3cbuugiQYVhx9X+ZlwWxeq2+F7G8YWg+G+wc7A+PBu82Yjye1M47u3xbxCOlG5AWi46nbwMm0SsMzrnhs2sBizhHdxbtdtb1K868JMArXQRSGvqfrLxcIAhDEvYb6UcVpFLDvRSaJcl1Zkm5Ii7Q+E9c4G8G913q59cHxxTX6EnBBEENj8Il2zefqBiwkfXpvhZks2LRnMRgom1bQHKuWfHpKgYnHKkhZSH4Fz.iyJXQMXyL38PcimrLKzWYUMXAIUpXsO0CmyPasRdg.Li1lkHuXGhsKiIC1bgRQFLT.aO0qc.61nLcdfe4OxLN6KLgc1YBOwS+nDY.Gb0iya6seT9A9e3lXIWfugu9wz4y.ObkK0w7ICX3ZoO6jddlyJqsKupW0RXnCAvqJQMRtyPWyA3gdysb5SkwO728BV5nczJqwtylf8JE7G7ImywOQCktk3ruvLxKsbmuFGYkP6rDHRM5RTbG1qz3IdJxx5KWeLhyk8JvCQbuS1ou5TkXmPVVFWdiEfj1L2ZKky8hWg4S2BqTCwBLNkqbMnoIoMhphXBzYOwMVKH4038dBdkwCWgAUBVqkf2iwjiWaIOu.QJH30d4p4oSi8V8AbNg4KRTf68IMLXsPVlk7LgcWzkTrjN.wjNwSWah+hng7xT5XvXxKpY1bGCF.m+bQpG3QpxXnMwAB.K7v74MryjE7dee4b4Kd.FWcL1Z6amW3Eh7q+w+L7S8O+eBe3+2dQ19I90PzyQo6VwRjG7MUviclc3vmZHCKTVKyvHYHKcnJVpTvPKAsirrUnC3Yu717I921w8+5Vk2x+UV9m+gK466uIbOeUF9V+VOL4NXzx4Le5.9S97dN6YKYR8b1ZRG2+a5.XjrTMNZ09TO088P36TbNv4bDCIYL7xCpT5.xP.5zqhUVhu7YDdzO2BN9omhwrmHWLbO2yH9G9gdu7VdyKgyB9FG+C+oZX9hDvxbmOkUR20MHzfEQrr73ZdM2YK228kpmR0fFVckLtv59d2YF7w.9nRcSGduRHjbiKRFsssDTHFM38oxlGiPmOU3nrrBbH3EG98HnRRr3IDwG6HDsjmWR4.3hqOgKttvq+9GQFfkHnIuKCbNN4pkbzU6qTY6E4vG7Xbam1vsbyJ2688P709NtO9W9+5uNN6sxhtyA14.KXP4Zby2ZKkiFQgQv2TSDG9tLt7kibSGcHhLGOvS9LA1Z1XJWcNO9SFIu5B7.OPjOxGcE969ACbv25XN4sqr9VK3werc37WbHqrVI5tCXyMWvKdlH27wMXMoJ7pZXesvpQkNO6yXbHlJP1KqAg03oMp3L4n3HPFexemKv+5ek+H9e+W5cygVNoBGkzF9a59tKDsGDnTv2+2ejll.de.KIsND7AhQPDCMXnsKffixbOqcnLVLSnoNx1SL801HkNpFMTjKDU290s22k75XsVDDJbFZ51qZoJSm1Q9fBpJcfG7AW5TQVpJmhEZpExJKwQGaesLr4ve3evE3a48bmT.8jokpVl1KWLqqDi.0QnqYYt5kCXMJSmeEFuzp7t95FRY9eM9WMaJG5T+2xkuvGEUiopsJqRgAlOcB4YEr6TOWdSX8KA4OXAKsbEatSj+nGdFyZf69tp3s7lyXwziSqjzmxe+ehN9G7ibV9V9u6l4.Gc.25cTw3UiL4ZJewGulMtRK+w+wsr16bMFMJwpbhY3qWI4XeJo68+8cuBLH7wtan.SKiOnb0sCLqdFy5Vvp0CvXgxBnqdATjQmORYkCqAt0xT7JMl3wOFgXmaeWWgAJduAW9H15pSwYREHaVzPWsxf7JD5AvE.uj.Phj3.onHuWg159bo10kpQ.cJZzlJIbTvz+2mT7rKc+DfhxNZ5Zv5Fy3kgex+weA99+ge86Idq9SPFrN2d9VR+LejycUkKrdC4ZNm3nFN9QONasXFyi07U8WJils+ug+V+f+V7g+YOCef2+siPWxnN.KObDaMAp6fycgo3Wnr0k63PGUYAkbly0P6NYD6h7ke5s4s7VVhqMQ3TGGxIiOzO4o3G4u+E387scbjRgyblcYi0GxEdQnY9xLvAW5hS4VtkQX5U5twn8IHzef2lTqULj92u7gLzzhvW7w2lm9YlwxqbDt6W6Q4VtsucJGNkA4CX174jUL.iLh5Y6IZEkEMsLO1g05vXbIct0qCkXrOV9U.wZobIvOQn0DHJF57Jdejg4I5ri8ngqaUt10liXKnnrjbcAVaFc9.1r7dChNbNKKVzvfAErybOylrfbyHrUATikXSR8TNA5B6RdlRTGy+l+uVmutu96NwppViJkLuIvjIyXz3QTUZ2ewy5LbsEA1d5XF4fKtdCK7NB1AHUvnUful+JFd2e9O.enexeB999d+4ov0w3k2Am8PrwElxtyFh5fPLCqIiKdgj9oCEPQ0XN53ob0MT5jJ949nu.iGMl5MFysepE7A9AWiMt5p79+.eZd020sxnkVAueBqrpfcDbsqBad0s4TmZDE2fTD79.Zzlp4Ajvj0Ij4xe4MHxLCHB7+yuVjO0i7k3m+m4Xbq2TRd345RrSDxF6XRXWFVLb+xsZLBthbFT6nYdGcwFJJJIuzflA0KR8twfwV5Z8rwT37aUvm4KrCusu5FDcNgtCfYzxr4UTdpGqCqpbO2cIOvcNfpRAwddLwSxzYJatyT1bKKaNYaFs5JrwUUN+EyIt0E41tkiwa8uvJr1AZ4fqNBMTy5WtFaXPRaAEEzxXZE3+2eSG+e7sqHpmBoj434y+ka4rmaCd2uqkwPG19Bk4CNVKyyYmMkNYLwPFabMH10RQtiS9ZsbhS1xeuOv8wm6O3WjLxv1lwZAC6rsRUbHG164ZysHKhL5fy40+5GxvwBW9pBaWGPpcbhiHjU.6L63ra8BxO4LtLF9o9kZ3C8iMm2y6ZBsWwwgNhEVdLcQk3TA2jcnZzXZhdjfOotbeVJ5G.dXhWQMkDMMnuRJ+spPmOxh5H0Ms8pXJ4lwGBTTzRtTgHNbVKVSRsPMcP0XghBKFigtt.gPfc20ipBNmiACbnsf3bbsM1gOwuqgG8w9T7s8t+KyMe3BhJ7u+S2w+e+FOFOzW8I4c8Mb38UMUhlnSgncLXkLNzIVhIKTdwyc.d1mIvexmaS57c79+abJN0Mu.HPlLfft.00xwO0Jz52hbcMDhDzF9Y+eZG9K7UGPiqQtAD1AgkY9jIbxid7jdmifibHFvYDFMvyQOxP7Mo9xvj2RdQRekwBKFikW8csLemem+Wyi74NGOvq+jTLzgoNhuVYqcBXGY4NtyRN4sZ4XGOUnoIMJCGJPWE00dBAG4VCGa0gXrvr5NbAkiezivG7u6Cx+h+Emk2v3kwW1QW8bvtLG6jUbvCTPUYpfegXR+qFWpJsc.YNXRqRlsBe6q.CBQRa9sssz0W4x8JhkpJiG.MSAqI0HLO2yMkO9G+Yvj43s7VuEt26bLNWhl4tNCcgF557IxiL4T66nv5nb3Rb9KcV9ROwSyv7uQb.cAXiKn7W7q4T71eGGhIyT9s9Xqyi94FvUupikFAe2eOy3tesqgWuFiqFwq91x4W+eylTeUC+c9wNEqbfor8Ni3i+q2wm8Qlylq2vsexR9V9qNmu5GZEhyUrYCwndluUIuuuygX88rDpoxvWHVd8u5pDxgXBDc8hNJGZ4.qlS2osrw5Q1XyIjUZonrjYSWvFSWvfirB.799Ne6Lc5Dt7Uq4rWbWPFR9vBhjyJqJbK2ska9VsDYNqekFpqKv2kHhKDRb8XUHz5IqzwgWJmpJ3geXOeCeSGheyO1F7bO+1b56YDc9TdTl99EQUkt1j.hLN.IRmNi1XKNyAHF5H25H9Jgox8TwT5emDmho+mkmmS6joTlWQUgPtUXzng7Zu6akxkFxoNsaeCGwHjmChqD6hN55BT2r.b4zALbrvJKc.LHolEwufboh29Wqi0V4P7newFdjGdWVTuBqcPkKt8N7I9L+x7u9W8+H+O+O8mg222wAInuHY5o489dNHAANwgMblmaHereiVN6k2flvAowVyG8W66g+u+2kwYeteQJqRoGWTX368uYNG4PldcFVivAPivnJkkFJXnifD.wQYUNp1hHJ6tigIS6n02xv7Cvn0DhECYAJu3EB7jOw5LdvA4HGcLatqGe1Zz1nXUngHW8ZBkWR3vmzvx4sbriLfm+ERJuRJEhMoBzEzD08sw.yZrD1tim7og2vCLhui22qheje7+DN9q5dv2rJ3gyuoGIjHyyjkmzvhIAPNJYXxDvqTlmnJ2ZeEvTYJ8vDYQ6I8r8xcsnvPndLlhjO7YSUpJfG7MsLCVRnUS8wXSKDBdDwf0Z5qWgMImbqPyTOyasfX5kBeDqKU6hkGufye1RltaGO3ap.xU1Y9bt+2dNu0W36fe5+QC4G3C9iw8+F9v75esGhHvq5Nh3oim44a3S+ogpk2kG5NNFS8afKdHt665ivu7uzOHeSeiawm32n.jkIDCbriOiY6NhQiEz3tfVRddGG6HIdXBwcwGJotUY3HCJMzoi4Jazw7ZHZFvV6pzBLYgR2lAFT.yqO.m+bsr6bKQTlbMgMVeNBQVoPY5hg7kex4rzRUbeutAjiPc8blNshgCDj7T47MVChKCIKo+zcafX2B989DVdmuyJVazRbtmcaFt1JPD1Zak1YKX5zB75blMSvXS7rbnCUvxKWfUirzJUr0UmjRL3kyfHDdoUFT6U5THjpVVdgPSWfEKVj7lHJwvLD7XYdOm7Zu78M8dbfrbCkkt9VzyRSim54yX+d.SiTW2Pgol5Eayf7RpxGRtjgIrDZyHtq63.7M+M8cwrq8I4W8W4bDCCIXNGfRab.OwSXvGGPdwQ4Z6VyhcOHQyDt+2XNeiuquW9c93O.dpPx6PLNfLpF3.rXxbHYcHTyQNx.LVeOWLCXisURrRHrybkycoFlVaQskbtKE4oNSfyeoHm+7vm+KtCSlnrn1wU1TY8sr7hWNRKUXKFx7vB7pv5qmwlWVPzbDLzNuiPCr601EQDxxDTpIxLDaKEChLbbM2zoi7hmwSlA9Ndu2LOyW9wQ5fhrDwaVYH41Lzvxr81YblmqkG+KMm+ie9N9rORjqsSRXHATrYcuxK+8dcE99M9ZOOB09TuJFECssK.0vnhgjgfPCduuWt9tDU0PpU45EL6fLC5HntMCqwSl0f0Y.IGWdNaucFG7PQVYUCWYyEfyPtIiKuYjbWKCWJiSeGuG9C9C+RDjalLyQXVmkW7J0LYdEEkP9.koyBz0BW87iX2hH2xq53TdhuYd3GwyC7fkHpPWmixLRjdXKvGlSzp3L.QGpYLquYjKd4H1B3nGdDcnbsYdVoHmbA1ZqV57Pwfb55fpkFy0ljTljrHPPLLoFxrJ6Nolis5XLNXwhY3aGgomWTM3nsErXYvpFxKfhxbN3gbbziXnrBlLMRWigy8DVtzyG387ty4e0uvDH.Ylbfkxl...H.jDQAQEnrHoADWNTHQb4AxKLzFKXRsgclAEttTq7YFfZeEfgvZSZuC1STs.hfuu2OUWhZYUEjLEIHLe2jRlbCr3xr6mggpF1qEqjdMA55ku9vAPQtKIs+E0DFXQrIsQzL0fKGNzgcr6tNlzoXkFtxE5HFyX0U95YiMdNLhgEsdb4BS10QmcKVdoUoqFVd3PFTzfQJ3LmQXmcWlu125+D9BedC26CZHSf7bOsM4jmK.Cw4f.yAE57J6N2yS9kWvEWWXVixgOzRXJSn08jpWWamRWWj7bEeKLYNDVnTOqiocaPvTgxpTuHPtwyz4Ur7xfKukr7VLT02PvCnn.LgJJrf10gXlvpkC4VO1XVZrPTs7kNSFnS3w+bC3q+acGVd3pDZTbKKLLOmgip4fGd.AQHqpj4KbLatx16.quUGO2YmSQYAG6D8pA+k0fHteOth22QsDIhmpdUp5HfJAJGIDsELKTiYrmrQRJ+VUHpF1qwfSJYQQhIiAWQpinypB.ED0NJJJQHmHMLXjPdlhedf3bOCJWf51kfsjyt9HZlASl86fYoC.JTkOfJUYPVKmX0UoaQfhLXmosT2ZIpvQOtPQYfMu15zMJkpkqyizMjLSukJaPnCHLfKr0Tl6DlgkAiGvxiKX0kcXDnvH3JBz04S5JvlijURr.ZMv7EdzLXAVb4GmhrUoxAy1cAwvHVZEGqtZMsAOMwJzXRsWG81gkVMfVHbkcTDaF44CIzZI1kXk0HkTeUOYkC3Qe9cXgrFO38e+bwm+4HFCbvSKbWulJt0a0vJKobK2TN2+q2v8d2FtqaIxZ4SvkuLu34Tt15JCKeE3gvSxMeVoPT5HDD.KYtTZlM0Fh8ERh99PLF4FGwD6qP6801ZRUJ.PSSDIl59amygoW13682o.UUFLHz1lSGVBsF15pJqeEkKe9MY97Ir1p8pGFEMzh2GPLYLbrkqtgxt6zg0jS4gg0Nngs1VX7vCyktXCPNhqEMXHJArlTkOijv6rxxCYqsmxEtXMKZxXoUirxxY.cb90sLaxHN7MKIUMKcTMLmXbAFaIRP5S6tG+jE7sw86+jnGLwLDJnWlpjYLHwLBMByiZhTosLv5dN2k534NeFFKzz0fe5BlVOlcVjwU1JxRKa3Ja9h75c2FACnZjEKLzzrffuHEJ1IbnC53DmZMdxmMPmGVzXw6eEXPDMPmBAM0HrVmfMDQCdlsaGCGlJRjkTs0i9Jj9BCZ1iEIz8MJ1+RR84t26wINrVSOKmx9JDN0+DsLbPNkNgEKD5jTi+LcGOW37y4buviwt6dYVckl95LnI0VaB8ZrLkozpqNjye9s4hWxyc9ZFxvgU38Apb4D0Yfn8cfXR6igtUvkkzcXYgfrixgNPAm9lGQQNLpR.77XOpmm4omwAVdHqkanqaGL4qhOzhOThyYRSOmtF79BblD05IwtBE1TGbG8ByWP+Sfxrcir0FJ0UJDLz4MzTWhdMCWY2HMdX1BGkcQrkKXdcIOwS0xgNVFab0yguSYV6BJO0HrNg77bZHUWGqUX3RBGXMAyKjjAYccp72urgL501JSmIDzRB9.Kp2gLmxxiqREbxCsso9xLDTVrnkoS6XwhqOWBdIiaf8MJz8MBhQsGmw0kfOv98zYVFLXnvRKIbriYv5lw4uvSyVW8YX9rKP8hqlFtH.HYHjQaCbkqLgm8YuDtr.268tFqrxA3xWJRlCFMLsn3jQfVPSajPnjlXV5zNdLlTmcuXZKG9.i3fKKLtJon6Yysb9ysKW7RaxKdNEQgppUH3s.Y3CcHBzz.YYY62OHhj1T78SBnrdrRp1gWqQHjpva.lbMOKlAyWjJOsZSsOHYfTAwhUHjUgjKb4qpbzaRXvvgztPXwzznNJ16pyzO5FBZGQEJGjTqNjjIfQbu7FDMcyvGSc07fp0vk6vkmQi2y0ltWJh88RolZ8NWeonkTyQhXz9QBzdazJ606EkkohWEBA5551Oc18sYvteKg3bcXniidLCCGMkqd0uD0KtDw5MHFlAZnWCjYzzZ3Z6nbpaZLCJOBW5hSwkCqrhvNaGv2AhoFQC3aUPywk63m6maAFYH9HzFROCccowePgALZx.UivS8jayux+1OBOwS+44O7+vixS8kCPzQnCrlA8c6dp5sqsVpcB78CAkrrjvUBw.pKPdUIRQFAwzOrQ5Xw7EjEcTfAWDbnT5TxcopKOppCaFzQfHvt6lPENb3AYysTlNujqr9tryz.MMcz04wzOhd7pR0PCNapq2ZZRra9xFxXX1PL.Uk8sYVT43GeIltqxzYwdw1l5USqExxEf7dEKIoYrPOCYBekdIz8+Yw9wNP7F7PDSkdhPW.WlMoJXQvRFVSG9vTHLGBsjYMj6xR8.hGZZ7LcFbPcAU4KwU2of55ZN9wKYqsyvGfoSaPk4jYF.jv69w+juHqcno7W+8b+jkT2HEN3XGdUJsBc9HtLKAfI6Nm+jO+mkCcrCwk1XKN+4uFG6Xqjj.muuYgjHkkoSg6ryBL1Nhc99QJjESdZVT0FLT2BcgLxLBlrRpauFMQOZrf1lFHpXlkANCpHzDhXzVpCSQiqxt6DXyMmSa.1cFXpLnwwfJ3b46qSSeLhD5HKK0jTQMkYjp5qvrLzsY4wWk11s42+2+Z7q9q0wu6u+5jOxzCdzi22QaWb+tfFQnqu2JSmzuwt5XuYAkzOYZnm3pzTMYOPkInjICpzH7ICHO89DVlUW51XPwxnTfyLXe8MfAppxnrxRU4XBAkh7LLFGKlqLewt3xfiezkoJunu8+ZXtW4ttyaluuu+uO5Z2S0kIK4gUBZH4gXu4TxsbqqxQNw8Sd1XFTTwnwkz5izE2qSozd8Jpr950DiQN9wVtWrJg9x.3nSyYQWAm+xJO1SF3paGAAFuxZDyF.E4DrCvKCHPIMc4z1kQvWfeQGg5RpmmTeluKRL3YzRjvDoJAOXrNxxbD5W6SiMIPIlTbc+vj6kGTYsRYUMui+RGghpCxEtv03W8W42Dq8o3ddSe.VaobhQGwXZBmk5+PoWyCIkrbi8U4M5c.RmjsXwl8Ryx358.R.6dsJNYnQCMMJnKwQO3qkqr3YQjAD8WOzhXfUVMiUWIv4dwcY2oC41tSKY4JO4KDI5ynpRXysmSQ1R.6jD4CEbfi.6bkmiegOxix28228s+spXCIkRIPa6LbEC4lt4g7c9s+Cxm5S8rbpicXdf6a.m4Elg1jwvAYLo1zmNpksu11bG29Q4AdCVVLaU1XijZy6BfXxPIxyd1He7IOE2zoVkZYEZ8VZwfQfVwfzOoF79HhwPP7jEbHwbZWr+YOZ6lwfQd1Y6F1byQn1NVdk39MCE.VWFZmtOKxhj57tW9wAvfFPOFus2bF+89AD9P+HGk2669TfNmkGlklET4B1gMTrbNZVhzlltNxKlhIHXCFr881n3AaTHCGl.TErD0cvOCJ0YDmWgQ.OWFwGngL55uSCr.LQt5NJ6LKvv0NL9UePJO5siKe.sljlKa6U18McZOFWA29cOGiyyyclFVzbIN8srFgVkhrVtxrcwyxncKSttARkv65uwSv6+G8GhO1u9EYhtcRlYlc.xXVHiMpGPKIYA7POniSbfLdqOzxLXnfDEJsKvo6v.0P2N47Ed304teUGhumu6Bl0NkYsSnVqvWDHuWVlRyyxwWJhm6fm3END+QORjsBBCrdbQkLwiQ6vYfBiAsArsNzAMoN3V63zm1yFWcHlhZxy5nahgm5YU9zeFkm6YxvhgbmfkVJsPnF1cZf.wzHk7UjHawz22lQT5PCEbfUtUFU9Z3S9a0w305npxh04HzsCw147Puoiv3ANz3xracp+M2avmtWlDFSxaPSsEusfycoVl5mxIN8wXdTYrbz8mWAhl5ohYSU7zv7I4LtxxMcDk1E2I6b9amRImL5Hyk5kivbkstfg0V0wkuhxjI0nwJNxgONqsrvlanLetgxrzTnK2FIxgX9rc3Nuiwr720+H91+td+7A+A+k36+usxxCWi5Zk7AOMNyAYmsBbjkOLCOzk39eK4b3SZXVKDMUr6rRt1k1g4yTpmdY9I9GbSb7SX326i0wu++9BV4.kr1v4nx.h00TsZEm9XmjPvRarkxpHFiv01EhRFwfxdicwlVH50z3fzXvpiooEFMLigUNdxqDX3vaktlRJKgpb3RWYK1ZmknsoBSlMoTdElNaWZaqHyZwZmvngkuBBYPdea64wQDu.24cNlupG793buvkX8m3HogRVP4LOyWfm3w9X7+4uvODu825QwZlPqLBDgHFhVHH8sTmI0Kl4wcIOOvsb5g724G9VYxjagCspAU2gfZoswfuQvRAylGYdaKs0QVYUOmVKoHujm6wWkEyBD6JSid.Kj4lfDgstlghRg77p8yXowCWd8Zt5Vu.Y42NNaAD7XLNVdIC+IOhx64ceOLe8e.9w+oeq7o9O7Sv+3ehGh66AgNtcVoxRw3YP3h7Fu6SvYe7cXqKFonTPZUxzVdC26PdU2VFuw6+V3webO+7+Lqy74Bm53EfKiKugmxQPnsFWrhSb3J7dnZkRxGDY8qZ3y9v6PqYDscfnFJx6UrNIA8JDX9bGgPCUUVFT43rmcFkEG.DCN2BpJJIhiXninTgfmfOmI0JW77Ur7RQ7cVFOxwzouRzCAoxODHhPDmAdausLdyu4WEMAnXTG0MYXivu8u8o4C9ibkzXHz.6NoiCVt2PQ8FeGu9kVtbZTCtGiwGLEGSiEX.lUUhXR0FQ7ivGU7tHiO.nEvjYFFt5oPZfodOipbDnkXlgs2Mi7pTt2yVjzR.jnSdQcKqtxp3CaSTMfoBevya5qB9s+Cgc1A9Z9K9.L5H+g76869iya5q8mg2063eF+P+n2J2yqCbLDqImJf+5eyKgqT.8ZbkcmvnQmhlNkm5IZ3e1+xKvEew0vOeINxQE1cdpiyTYLKpUdpmYLO6yD3ENWC9t04M+PqxQOUIW7xY7jOkEptJKVLmrLKKMrhXLPaSMdeKscsnFAGNlOMxEt3cxW5K+TjkOmm4Ly3INy44UeauctxlMbo0mvEuXKG+3C4VNUIccJO4SsAMXwHC3jmXD6tS6q.pq8I05jZHzA3oAUxX3v.NcSFFOLCbBAAN5gWikV4T7BWvvsrYj1PFUymkLCjDSmWmIRsOfjMo55BnicRoB0UfkbFOV3K+BAlMUosVY1BX9h.MAkIyU5hQFrpg649din0QtzNFxqiTNHic7BW5Z0XmlFZo6MNhlMugEK1ka5lNDut6ZYdaui9QjHagyrLG9PNtyaWPCYTspvc8V1la9N9w44eZOW8pve6O3Y3duqiwG9mdYJEECcXrIkl6bCX4kVgG8y64y7GOiM2nfhibDNxoEP8Tk6Huq.w1RaLRLVxpUdLQKYqF4HGaU9q9dOHiFH7o+bcb9MiT3NH6LIM1EGNHMoea5fEKhLe9LFtrgPSAKOzQlEtya+Uya4gFwhZ3jm70xINovVasDhYB2yq6PbxSHb4KE47u3BdC26gog.27oJ3ux2TF1L4kuYe8s06WwSmKmPD7g.4YATcN1ffwUPKk7TOSfele1ygK+HzEfEsSX33QI8W5C6uojFqeIOECxbr4U8Tj6HKuFmyRaSFNGb3CI7ZdscLegg54BsQap6rBJssJXDBcvK7rJO2KnbamJPmeCNzgWiUVsjs2AVZDTWOk1++at2zfrzqy66624bd2uq8dO8LX1vNwBIA.IfHoIMYQJIJvXGFJpUSYaE63XGQ4DEkHYIYUJKRg1NNVJQkEisbbXBkJRYIxnHJKZYIABC.tIPxAfjXGydOSO8xsuauqms7g26LCyWBP9PpJcU2p5Z5kZt26oOmyyyy+++92XHMoKp.GVSM00oL5.E+D+cB4McaJ5FoAkim4rR9U+3i3R6rGO7Cd6raInrfSCEUdpzi3hmqh27oC3At004R6dHm8rV1dWMIYYnRTDlDhJxSmdJJoAScGrMPbLnD6iWzf1MD7YrTWHQIX7XKm7Ddd2uuDR5J3odRCewmxgT.SmOgppBBWfSNstlhxbJKyoxNmdoavC8FuS18ZuDuzq53C9W5T70OyU3fwIXbmmA82fCGqorbN85.V6bZZZHLHkUV+cwQWSvIOkg0WU8ZuCQRTBdzX8Vv2RzEDRvKQIF1xwQrX8kbKmNhele9ii01xzHoJlhw9a.qha.SLtts7g4TPjLaAoXhvXZaVERvPIx7z1lHU4WzuBX1LO44sc.Lpqi671TjOySbT.d5QUcDAARNxQ7T2XHHnUDvNaq5sTpXlbnmyc983o+J84guuA3MQfos6eu+2+J7q8wOjzdBNQO3fq5Yoi3otQPuUWk6+Ny4Mb7L9K+cmvkNHlu9W2vk21SiCN+1ywKRPF19WxK2MhxhYnPQ.YLa1R3rRxRZ6CfzOmNc6wJKA20cDgvVghTxB7jnfRSCAJ4BgJqAw0Y5kjvvLBRi3NN4I3NtyHdxm5YwKdSn0V7HX3fDxK2hj3koamZhBBINRi1zBRdIob5aQfTZ4EetJFuZ2WGGYnAYPHJgAGkHQRXfCiUhyG2p1IshnPCRYNmd8.bHIhD1ambN5lg273AQvB8YtfQDNG1.IBmj7IFFzKf44dlNaFY8Cn+vHt7UpAojYkMfH.YPBSOrjhBGIQYjt50PXGvjQYr6Ucj0qKM0JhhEDjTQYSJ00ZbVQKCsafrTHNnUBfgAKzmg5pf+HTNSx64unhO0moCyKsbqapXqgZxKlA8VgNKaw20y63c1JblMVsjG5sjPmtNN+ErLbXAIoYz3cX7GfvrF8h50xBRqg9QATT.M1VgqjDXY8Ubr4Zgb+2shZqlkWJisVSwfjJxhhPohnopGZSKPXs1VlbIERp8y3geK8YsMDTUeEtqa66g0WeHuQ4.pafF2RTNO.kTSitWq63VVwINVOVaEAxTHLpgw60k.o70tODhPvK7XrA3MAHHBsM.KBHn0ITpPZIxhoK55Hr0AzXfkVuCDpPFGhHLhZgioMULotfBuFSn.YSF04PXT.Gl6Y+YZ7I8vGmwdyBYZYLHhIKrKdcB3fZRHHKCSDbkqtFSllQdtucfTVnWeAU04XZRQk6Y6lqfAHqocWo3ZPsukxfk4gtuZj9FvcDLROil4Y7TGejObOdtGGJipnxzxoIDkfKfBy9bvzBp8FxLcHYJHlAUy7njqPsqc9BM1NDqjLeFnqCPnBv3ZXvPMm53BVc3bFtbWRR7Lra6vnxB6ivCpNfN8RTOos2MF2b5ujfIkkz3fvHEdQCal8M4uvCo329+smg9CdaLXEI44dpp73zdhbF1b8cXP+CINpC2yaXHuq2ceN0sZHKSPpPvnq3PZk3d8HCes2hRnvqBPfnUeDpP791ApH82DhWsc755ed6CEp1IgZLHEB5Gm1NAUGXa7sdiz2JnVsERRCIISPUkmQiFSRPFdaH0MNLdKpfPBUf23QzHPWVgHpKARHMQPYUEdYL8G1gc2yye5elkSe2C4c+CYX+si3K8sMbgRCu70Lbr0D7PO3pn.lkWQbeX+8UnUNd3GdHetO0Kx27KeBdn2RMB4RjOWxxABZbaP4zd32TgMXB4RPjlPbGIgdnwAXhHVEQSomtYN1XSUKXwjs.PwogwS5fyq.qm8Ozv74UDlXIcv.JJgidrMYRPKTyxqR3RW9P1X8gsSXtFJxU7A+dem7jeIKW3xWkSdx6mjjdLdbaK7ymC20smxxq2gplbNbrlppHZpEX0MXpUDmHaMIscgJ2dsVPnrsYRw0UJv0MIS6Yh2nao2X.VWurxVhuwMRJGrsy+1KZ6YdSMTWWiKMFiviwYopogjjTBBDzLEz0BxVIDakEmqAi1gnLj55bhTgDDpHVpPZauaSbJzXbTTZorIf+juvYoaxI3m4GYERiK3nap31Othyb1.Nwlk7AeOo3cyAYLc6kvbeEWXaGlqTwwOQO9a9e7swu3+MM7fOPLypsHCMnbgzLNgKbNKc5JX0U5ydyLr+bOyq8Xps3sdBPRhPP2U1gkWdYFNLj7RX6KOmoy.gOsElXZGVsEgqlPoFT0D20STm9jk0gib2NtvE0ToCIqeeNb7DrM8QIf0VulkWNgeyOwSPV2UYvvMntFxC7bscpHTkf0BIYPudRrjyzhPzMdBi5h2VSiIBsqUo6dm70dAQfuknI2bf02rSBdC2.h6huiuf2eyKPVWsfx7Kl6d4hA+3TfOMFsiVtWK7DD2h63pJOU0F5zoOMtVuCDZCnun0moE9HBDgfCxBiwo8DH8.VRRCoxDvt664UO+X1e5WhuxK8Cwa8MGfX3TRvva69RHx1CWtFQmX.MEEAb98qItaJ57Dd5u7Ldzu6A7nuuBdr+LAOx6VgyMFuYEP2vEOml8mpnoQQYYD44KbTsqgtoMr458YPGIN4VXsv1mywktpioyBQpB.YqawLMIHPRnH6F761N2PRWOcGHnixyIukXR6z95TXvPt51dPjyG9GX.+Ne5s47WIm2vc+.Kb8dqarlWZX49sMgSagrtwzIqgYSaX73XVsUwgs+LKvsf+0yrLrgPsGZVrUXs0Ssq8eqVbyiKttj4t9hAqs0rt9ETnPDJvofZui41FJ8NZB.u1iy1NTr9cSIKQPQgmhh5VQtV3odtGciDiDJAZjsN2lpV0fW2TSTjbAxejzIKfvPAOza9MR99GvG5G8iv+E+m8x77+4cX2q5H+fTt5NMX6DhQGRcSJO4SVwroPXhirLASFmvW+qMle3+p8HIZW9ZeswX0Kg0Bm3Tor9l83vwB18ZgLeVaR5jjJXyMEba2VHOvaJj65tTjk1hiXAf21BeTk.7VAMUswb.dPa8Lur8QYkkxhblmWhtoOVKTUUi0DPVBzueCeeu+97hu397Xewmms15dIJNAiGjgvtiJoWmLL112OpJakrXXXFEkFt71NNXeOVSDE0fwIw3Z2s+0tODsKKH.IW2L7lEoKgEHAwM14XQvsrHWtZqhPoBtgBqcKfTgcQRi4Ds2SyXL3PPRmHbNXm8pnr1Q+dIj6Azskw1DJ3PimQGVy.YDx4dv6HeVEqrTGlWV2tKUPDW4ZsmIN9Jd9pOmiuwy+3LdlggCGvI1LjAcWmO3ekag28cVxR85wi8mzvQtKGO0WqAqOgHgfDulG7QDnEw7a7arGowC4c+tTDGz9+msuZNMUNrtPrNKqsdFarojMVSxvdBNbuZ14PGoIQTogctRA6tWIkEwzTmPSCjWcMhiiQphvKBHJJhzTAwYfJxy.ojW3Uy4RWQScSBG+Tv8c+JlLRyu9+iONqt0cyZqdKnTPyBDAMc7ThjQH7QbO2ifrNvN6Am67NpZJoSBbj0x3VNphR8MkhfP75gwTnwTUQnSfHLFbNh7V7wAXEBfVBi+cxwxaJYNwB8CzpCy.ODZb3ZLX0NbVKyaZHIqCMVPW3on1iwHHMK4FLojhojL0QnuAqRg1JHrSD4JnWfB8DOUMsPMotog.EDopQDFyouWI20cNg+BukuKZBRnpwv9GpXkdB99eGg3okqRqrpBuQQmXENITU3onAd7mXFum2SLe3GcE9DexWkW87mBgLmG86YHOxCOj.KLZriJc6NnM1F7H3vwJxq.jQTpaedr9lJN1wFRnRQSMLYrGUzVHUsZW0XYgFRZMUbUsESN3soX0gXcGvi7V2hjNB9G7K+oY0UdubrisLyKz3kgzrXhx852i7w4LrWBoIBFMphqbEIkUAHDgLKu.mtDitCquAHDRVjvauNtCQcM4auCS2eLAlEQSXVJCN1FDt5RXTeGKH7eGIp208osyfv5w23PmWPw34TNdJUyxQW2fckdbhSd6jpRox1dYSgTRRpfo4F5ZzL4a8hL5a+hDUTPxVavQN8sQvsNjqpM3iBakEqF5kJX1bCAgBFzSRSilzm6wH32+Wiu2xknROgltZru++a4YW5Vw3WFgHDs+bTWsDlocAeAEUQzIMfB+bj1g7UeBKO3CI3uweiai+YehJ17Xgzou.IWApOB4GNEeXFZmgZSNxzNzTKHLNj4SlfDEAAwKzsfmzvEJYW4oQKPWWfHviAIMMQHPg25otLGuUwzIwTWa3G+u4VrzZR9n+m76Qb7Cvsdh0nvWPmNYjWB3snMZ7h1IZ5bPZlfKboFlMuKQJAgwwXsJvoXzgN1ZS0BVW29GyulKHph6h8m7mflqbVjRO0NOywgWEf765QYo+g+CXVRb6Y2LALC.imFw1jDeL74AL2cHyBWhMVKgo+D+vDewWk.7fWgR3Xl2i3c9AX7G8uKRNAgpFpIfU+s9MnyevuNItVPe0UoHQFxqb+uWb+s96i01CZLrVfjBOrm1ixXv0XIreexm4vOugvfai8ImMMu.YGVviWjixuDYypnteHw4mjjkuLiKZM+RsQRr0iHLkhJnpRyy70q41Nce9a+iFyS+hiXx688S7C+.n+Y9Uam53d0bsfDVxkheZ.GtrhiUVxxYor6hi1FppwqiIOWPSDD0uF23DPl0BRTqEmQ2BfUuDsKiYi1kM2pfO7OzsynC87y7S+Giycmb+26cPYC3DszCNNDvnvznHuZJowdVdoDxK7njojE2JD5lZABQ.doFm0yz4JFNnUo2gQuNHYqZhFrkjFER3u5GC69gjd1sge+OMtuzmiW7WTvs9e4+CDrh.8bIE8.mRPc9Qoagm7gBBNWCA8cnm4XTYLC7on949XHUqP8qrOY+q9ofm3yy3S9e.C+KdbB6Zo3y8mf4y9wwHDT7neHLu2OHGtmjfu3YYukGhbOEGVY43QR1OKkhPKKk.QK2mIG3wVNkdazi859njdj6jnZMx+r+Er1y+ulpKWygoNFueLEGX4H2hhMW+nb1WnfcG6X8HAUJXlHj9CDPQ.GLIfxmsfic6o7de6qxp+SGw3m9qvW4UsrkpKc5oP4fnNoL25ndVEwKGSxghab2owMgXojtc7nJEb3ERn2RsyHw6ksJCqo.SygDmzid8h4Au+i08oMvC..PAYIQTPTwJqJ3y8Gn4ewm34n+fGj66d6wj4iPElQSiDrfoos2CR.oHFu2gQSK9EEN7VKdeDwgsZGsp1g2av4aSkOqu0s4ulKHl12vzNBzWUS268eOh91VhiLjqWhIex+yY0m9KvzyYwNRvfkxHouCewNzMXEhRU3NmF0o2Dw0bnSBnmrlDolfS814fltL13Xi23O.IeiOEQe4GiYm9sQrvyp+t+pDK0L+999Ym20eML8tUFsiCywtOJBfA6CFcItkhIsdFhAVbxXr9dXxDXLcIZVIMUIXGd6HbvRbbhEADtmg7PMSdgDNxwcLqPx3CqoWRLaNzS3LO41C3ntbDtDFYTTjtByNHhK776vCZVgN0ZDq0ixyNhCSaf9CHbyLBSffJI86mf0TPRPFAGLlDgEe+DpSRnY5HripP1+nL8.OIoPPjf7bO57DFNLkSc6JNxwj7LeSC+l+KuHSmlvG3QuaL.W9pMXoaaXytnrxlZvpuYKAjhf13SHPRudQLqqlY4huCJ.5HHP0V82hiLbudng+xkwHLN7gfeOGGbQGSNrhdK81XkfkIJuhcdt4TsbG5u09T9Y+cY5m9SguHmxhwr5c8NH3W4ihL4sPcFzwOFOFlTH3RujE4bX+3ixZdO4iOf5y5Hs3Zr10dQbARtvO3OISsqQz+VK1cbTzWfwC0MB5PMgi97bpOy+SHZFAHIHvvkuuuWN2G3mmI8Vhk8dJaLTLWRTQMgBnJwwAENleQOWaYKGYOEqYinHYLlW5eCG8webVazKRGydbI+.DCtcNyG4+YZtcIgSyHL+PTABVlb9w+tVkmYWGu7e9HxqR3ZyDbzpIr0slBe0uAa8+5uL82cexHm4wC4k+t+YYza+Q4v.OcpgjXMSKEXm6Y3xJdS2aHIIBdgm2xu2u2db9KGvlasIm91BHJEzNCgYB19xgr29vJCZKyuP3PqLDHkHPQVphdcE3b0zMKld8TLOuj7RnptAkTPm98WvEzVA3HkuN1gXVpDDRrdOpcLT4EL0mR1y8sHvOklA2Ox4RbROy9+7eNkm4SSPu0I41OA81ul5W4Kg4m+UI5e3SgeTaEDElPNT1B67k287L7o+THC5BuwOB5IZ7i9VDIUHC2hZ8pzriCybO1N0zONAmFhxzbjK7BbG+o+2gyWvACOJl0NFG4BOM2xY9bnm2iK9C9KRxfFBh7Dg.UpFozgtiFuHjfROokdFY8juQEq7676wo9L+yHvNC6fdTezakUd9uMclsOq9VgCOye.C9G+KPlpKkNC9csb4ev6lsvxojJpem+0449K+SxjvAn9r+evveqeYpCMbgSd2rlaD8N+44z+a9MPdrGB6o2fd4SQrbeVqufnTASl34o9pFdwWvyd6qwK5vcbp1Kvlj.ZMLad.0MMrwQzrwVJTUpVp8VoPqWDzjABRhaGhWXT.AohEMPSgZtinv.RRBYsUZKeVHAZ0P7q8BhXfoF.eDJ4DFNygZmWhU+hebjBH+C7ihIMDygGf3L+9jIrT8e+Gin6994fCho6G5An4k2kK+LWkfMViMCBIJvwp+S96wp1TJtzqf1Mm4u8eLb26cf9akSyd6SiPh7juU76US8UBndtF5UP+tonVQfZoorwu+mjZlyk+K8yx4t+2OGJWmtuvqvC969WiMd4+U7BO02GM2y8fqe.t.Ek9VQ3lDFP2XAtDA44yXvRgbhQuD6++9GGr4X9E+on7c8CfoZ.K+e3ife2CQWGf+TO.q7y8OASGMh+q9ovFTf687OE0DKW0Wg8zmlrkiYEyNz6O82lAjyeza+iwdOzGfSng64e4+QHF80Xze9mmIoeDxhhXmcGwk9pdt3ECnVmPRpBorggqES2tPTrll5V.wKjsQNYRTD8FBpnqP0dag2Ccx7X8xqmtl2f1OoQADF.1gBLlXVZXaEgggs8mPIZOBw6b38uNZccn.xDAj6qH9ezGAw4t.U1PxC6yvOzeK1388uOa+xNzeqmD7ygNYz8BWkhmYDh8cPxIHr5JL6K7RnenNrQCHcF3recDLgUCrX15cwgeO+swWVPV2A3C5RotgQEWkozNDqdhPxF1ijME3VWfObLbs+czHk3tmODAzEyyVytMmlZ0FrhaDctxY3fdO.LDjK6wHUT683BiwEKXdLz2rLwSgxO+SxLcAq+C9gYv66GixKGwAujk4Uavzpco9O2xvnix0N9wXZbEq1DQ1vgb0i8NvIgyJrrdoh3K3nmbW7W4kPFH396FwW7I+R7JSzrTgg6RII6atGOcogQcCPV0mkFBK0q0E7N.OAjFWR2LvMOscpxlbBB6Pbr.BxQ3ivTtENSaX5Fntd31tvvydQKoess+d8NHJxgRIQpttwnsfQgS2PqnkdcrfnsOIRxTw32eB9t2BpUtGxeKuA59g+wYmcqwnC3Hu7YvfkQSNjU+U96g2AcjZF6bLTFyRW8pL4hOB5pgT6Gy3etOClm3wX3S72mvseRpdYOkI8PQAzujzfNbp8dUtPSLZimpTA1sTHWRPWGjDERZffpdGiqQW14RdLaCyS8b9n2.G097DekWlwq6QkWw.eDYNEJg.YsgTgmUzVx6Dvvj4Xd7u.wVOwu02G6eoHzOmiQimxpUWfijDwYl.ENGppwjcGcHHnGiq73BlwUJ6wU2G51GJrN5GtGNcECUBV+y8eJePeq5oSDFPBkhcw6srpQhZflNYQsS.1WSbhffnHvmhnBpp0nmGRdYFqsNLXUnroC049VeZbcNcrvxjVuGgTcCaTBKlqjP2NGcQKNmjpV+aHDcAea7Hnd8zXp1FPFy95Rh+0eBxehdLOGFrjfcNiCeWKtQAz83ucrW9yvlu0GlY+v+l7beYIKWBi6UPlHilRvcs4DZNjZYNa6Vk5i9goe7eLp5mhNeteRN7M8eMWYoU3N59lI.Axl8ve0qgNYcRplwR9PVJOfoqKXV8PNMdLEivMZFQS6PSYCt0BoW7Xbygfziyz4P2rD1qtl.8X79.5HiowAY0JvzV6egKGaj.6UFi153.imfqsGIdCyMFRNolfWxgyuDchUHc6SPRJc8CXP8HRx5w48dZNTfe0k3cjjxr9av+t+J+gr6y1vgWVwTkjoRnrzSvXPNaJgK2gPqmUWQPbVLkVG0MNzBI4ZO1oMX80zakt3Rgyuim4yfPOjE6oSOZCxtEigtUfxK9bYq9PZZ7TUC3TDrf+EVKHc8agbhSfHTPgy9ZObqVTBOAuGRzETogCJLLaZNlcZH6hwnxfrG9T3jPwy7r3N24vDCEkdV1VRG+tDFAtgcfzHTnPtCHMk7b2wOMEptbzCebN5q9Gg.n73uA1Yi6mbik69o9kfq9xTj0i4cxXTl.kWSh9ZrcbJQlbh9VeUJFCEqlwpwkbh7ySfHfCu+GgzTMtJvUjf1OjbqCg6PjYBtZjmwwJ7rDcVa.QZM5uwyyTK3N6dHex+WXdQEQBIGOKlktkDjAPybONYJ5CLbsHX7VCoSfmtA4TL.NWwxrie.CleQxJpoqLhUVRxw2nlae483N6IX4XAUzivPAVrLu1yn7FlVVRotUqIgJAacrNrzpcW3.+VJ76sSILrlvPHJnUEUJQq53CTPXfmPU6Dfs1alhgBZ4Tw0+9BBtN1EBZy5LTn9E9k9k9k9+oEDIzP8m3SRGcMoee+UYuC5BSMrZhj5AJhiyIpWHKemRZ18aS9YOKoW7Ph2cJCyuJom62F4y9Yg0OFtisIK+0+0wXLL9s+2ghIUj24HnLWgNi9Vzq7UYVmuKBts0vu9Rr1K+EXXwqPTii3DGI68Br4S74Idublba2G9t2E8+1+gr1EeLhtxknq9h7F9F+Brb044h89t4UdSePZLoXKf3TAmb1Yn2AeUHNCuIf6JYWDG4Vn6FJBL6f+o+pvEeVZN+Kwfuxml3wOEYCxPY8nuy2KWMLDsth0WOlrK9jH1aWVMaBcN7U3VN2uK8kWlCu22LkxTb0i4D68Mw9L+wTraNY0E7F192h6e6+4bT0qR3IOItsFR+911wburhjgRB6JIq6hAbEKX7LX5bX17FxKJw0zPbnhNwQDGHIJZwED79aLxYAszt267TV0JNo1nm5F.63FSl15As4l4X5q4QF0EUTlsDiGMityqIIA7IgPpkdGMjNmJlLAHVYc13i9yxUJ+XvYdb1ZuGiIXY.vzvMQc7NDcDIAgIDXanmt.8R8nXrm8ev+tz6ZOEcptFq9B+NLekOJ6+lemj8A9Gyw9LeTN19+gb5C9r3vfRjxUB+Q.wCQm64d4bOxOGG8K8w3Nq+LDrcFFSA0CNAW468mFU7.BzNZbZpLSXdvgb6AB5eg+sDV9Xz+UCwe+eETQP5G7uN5u1qx7u3eDke6+0LHYKBdK+HL0dMjm4E3vyNmxa63rwnJ5Gnv98+g3v+QSXyuvmDsIjTol5x2KChxg0S3huseX9SNbCdO67qvsW7qgrLD7NdglU4EW9Trc7pT48DecLCpZGCcoVPSsi5ZO5pF1eVLJADEFRbXHCREzuCzIBvCgpaRbG72T7xFqXAzSak0TqLEZ4Q40ySWuew5C2MyU7WWi+Nc1AXt1Abn3V4Re9JzIgr4oDr5ZRRtk8vLXcJpEjEIXum2xjuvKg9riXuIZV8Tag8XCQ1AxYHc6KvTkynIYXtbAcmVg7NVFu57TMe.0WdPq2CNJrxx0LsNgq8Bmg0douMc7Ejuwci69eGzbRAtcaP3Co7kOCYW7rXl0mq0+TzbGGi3tAn2dLuPwRbTCzcSACOdMd+drcysv7y43G63RFzSf9tjrwcqn6TMMO6Y4vu4Nr6ztb3seubrMpvOoF2kGx4tpgn6NfMdiJ1XSMAxZt1m4KQy1BhHfcV9MSwaqOpQEr8rXl87N1NWPuW7LjN8pbvfM3ZCtcTg8HPASLZB5EPPj.BgFw0iqf12jDNnILm9cxnahjj.HIDRiZU3j0VSv+2FtnbA1HszzXZ0GRPua7d40ofeqB38s.newlKP6EKec4bqhdqPtrCSujmNKGPSHTGKPrp.yvMI2CcK7nGUR5VID+duCN+WNm3qEShdOJ5Oj4BnbjmvPPpRIPOilNcIOIsMmtO9oHcrgxIs4jgcJTsdJq2.8V9HL9NtENvGfUkfZpGwEpwzzPiI.+QdSLu2ajwWtg49PBmIndRIB8RrbAzcEAx9NlF3HStAI66HrZBKGtLME6SzrkH7pVjaER9cbblxsx7C7Hxsb1KYYkxHRjP+MBPUALqA2oSnebBSeWucJ+JJ1KOf8cvxWxyFtRhCBXuGIjtWyy7n6h828N4.YJ9.HwNFsHfljtDEOgvjHDART3WjJxJjh1ntd4izitIsk+aa.g2gP1FXtNuGoSci2o7tVnx50BTHvu.28BQ6tGWOYCsV2MhGAKtV.u3fnWOwifPCckPJwnCzTsNzwJHpSM5k738cIXtlPY.93BhBMXCSg0iHSJnZLXekCotqGeTL4iSHbCOwGuOka6nmXJLHCSTDY8rXNtg4iSoqE5WeExOxQ4Hx9LJLksm5IeFXGCcrQD2Dwx8mRPkk4YKS0FQjs6Av7PFK5RnG5uJjtND0WQgLEQnfzgfUNj85C87qhWJX9bAhIPZPBG6HdBMNryjLKtGdgm8vRtSgHFjARx20SPGvmzg4qLmQMAj2.Qmqf7dKQ8.PkBCNojj9wD+JGPuscL22gxACoi0yQKaXm9gzqaKBBERHHbQoBp1XVTHZCA2lRZY.whrJyhBjQntIDevYayiSqQf0Ef2GPZzMOJ45eedu7FHdJToHDvXc3rxW6iLzdMJQ.IFA1C8L8.GngNK4IdqBryiQqiHLD1OD70FryrTFFQ3qNkqp6PmovrJOlXHbnGYPIAkgTiBuTQug6xg10IzJPT54fsmSh.hVqKkQPBkL+fDFsmmw0vPMrLi47hADut.QhfgZOE6WyNtHz4fZhgrkCnTNCY2djFIPqZKUqowxk2qgd0sDfWHZPDOEFrJdCDnqY+cbD0jv7ErXfjBD0YT3Mzci43rYXF5QckXlH2gnICQFFf+pUbogcIbXCG26g4Vp6lwXMzL1RhSQiGJMsjo2DIXXFDIasMoW.Z7Xj0DDIQ2ThxqntnglRGJUBNYLMHvIUDyN233.igEw3baioDBEAtysPM7JrVOZsE8BrFIkA3DUHbdxmNCrtW6EDBZwnmxKvpaiIIY3BPWnZEZqW11m8pRSaB9pZ4AYciihYsIhWcsAuS0FvpAKL+k22Fp4K3os2u.fY0tEgCqjn.GJohxp1ZoGMJmn3jE1CzfnqBARBBTn0v3w0TUpAT38Bh5HQs3bVios.ckTf01BqD8bIFuCUbvBT+4vYZ07nt105XsExDTHDbyTpuc64pZCRe.dim5JCZsEjRTQsD6SnZMHTcCTVaPq83oE2PJk.kLbQfyzd1tw4aCeVZwRDFeKpi0Fb11G5lb7zPRb.U5YXMhVSPIT3LM3rFDdMM5RBCVBvhVmCnott.7dBCCorrjxhygR0gj3gjlL709Hi1Kcz9lyMhaYKzzzfWnPQ6KnFiqM04UgDFJnr1SSSChz.hRkD3iay3oqKKeosU3oEs2985agoTrfqiKBbTmAuArBIAcfXaajNgSRrH.YPa5xcca90IKlzj3VELaaE0aa595WrkY6kobNZiAwvfaD4AW2DxsOWABkDtfnMWuV9qeCcqErdGAAAHbsIDTTXPap4Ja6ei00Fnr3knjBRhamqPK2sZw1XSi65j1pMBE8skG5EsuNUWVABUq9TEs8QnwnY5rQXcMLO+kIMNkdcGfRnX1rYTWUfvqw4MjkN.u2Pc8b7tJZzUDHgj3XZzFz54nrksV6S9+KXc8+e0GWGfmWWs1ZcqBkrVOHjHhu4FXtqqp6ui8zz51HdDgBqQzx4Jm.4024YQ1JdSlOwMZo6Mq99++6GRobwy6V9aFFDvfd8IMQgR5opY4EIbXHRjDGpw6z2XGhzjifyooQmi2VhVWiRBIIozznQ2bVr1.r1HL1D9+BxNCpWPi9rSB.....IUjSD4pPfIH" ],
					"embed" : 1,
					"id" : "obj-1",
					"maxclass" : "fpic",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "jit_matrix" ],
					"patching_rect" : [ 454.0, 594.0, 140.0, 87.0 ],
					"pic" : "percolate.jpg"
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
					"text" : "• by dan trueman, music department princeton university"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 1 ],
					"midpoints" : [ 121.0, 252.0, 64.0, 252.0 ],
					"source" : [ "obj-10", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-16", 0 ],
					"hidden" : 1,
					"source" : [ "obj-10", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 0 ],
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-60", 0 ],
					"midpoints" : [ 32.5, 294.0, 209.0, 294.0 ],
					"order" : 0,
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 1 ],
					"midpoints" : [ 32.5, 294.0, 104.0, 294.0, 104.0, 531.0, 52.0, 531.0 ],
					"order" : 1,
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-64", 0 ],
					"order" : 2,
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"hidden" : 1,
					"source" : [ "obj-16", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"hidden" : 1,
					"source" : [ "obj-17", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 0 ],
					"hidden" : 1,
					"source" : [ "obj-18", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 0 ],
					"hidden" : 1,
					"source" : [ "obj-19", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 0 ],
					"hidden" : 1,
					"source" : [ "obj-20", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-25", 0 ],
					"hidden" : 1,
					"source" : [ "obj-21", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 2 ],
					"midpoints" : [ 348.5, 259.0, 95.5, 259.0 ],
					"source" : [ "obj-24", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 0 ],
					"hidden" : 1,
					"source" : [ "obj-25", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-27", 0 ],
					"hidden" : 1,
					"source" : [ "obj-26", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 0 ],
					"hidden" : 1,
					"source" : [ "obj-27", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"hidden" : 1,
					"source" : [ "obj-29", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 0 ],
					"hidden" : 1,
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 0 ],
					"hidden" : 1,
					"source" : [ "obj-32", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 0 ],
					"hidden" : 1,
					"source" : [ "obj-33", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-37", 0 ],
					"source" : [ "obj-36", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 2 ],
					"midpoints" : [ 137.5, 534.0, 71.5, 534.0 ],
					"source" : [ "obj-37", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 0 ],
					"hidden" : 1,
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"hidden" : 1,
					"source" : [ "obj-41", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 1 ],
					"source" : [ "obj-45", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-45", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"hidden" : 1,
					"source" : [ "obj-49", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 0 ],
					"hidden" : 1,
					"order" : 1,
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 0 ],
					"hidden" : 1,
					"order" : 0,
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-4", 0 ],
					"hidden" : 1,
					"order" : 1,
					"source" : [ "obj-6", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-5", 0 ],
					"hidden" : 1,
					"order" : 0,
					"source" : [ "obj-6", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 1 ],
					"hidden" : 1,
					"order" : 2,
					"source" : [ "obj-6", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 1 ],
					"order" : 0,
					"source" : [ "obj-60", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"order" : 1,
					"source" : [ "obj-60", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-45", 1 ],
					"midpoints" : [ 71.5, 570.0, 149.5, 570.0 ],
					"source" : [ "obj-61", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-45", 0 ],
					"source" : [ "obj-61", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 0 ],
					"midpoints" : [ 89.5, 528.0, 32.5, 528.0 ],
					"order" : 0,
					"source" : [ "obj-64", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-65", 0 ],
					"order" : 1,
					"source" : [ "obj-64", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"hidden" : 1,
					"source" : [ "obj-64", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-36", 0 ],
					"midpoints" : [ 337.5, 307.0, 318.0, 307.0, 318.0, 343.0, 137.5, 343.0 ],
					"source" : [ "obj-69", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-73", 0 ],
					"hidden" : 1,
					"source" : [ "obj-7", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"hidden" : 1,
					"source" : [ "obj-71", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-32", 0 ],
					"hidden" : 1,
					"source" : [ "obj-73", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 0 ],
					"hidden" : 1,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"hidden" : 1,
					"source" : [ "obj-9", 0 ]
				}

			}
 ],
		"parameters" : 		{
			"obj-45" : [ "live.gain~", "live.gain~", 0 ],
			"obj-60" : [ "live.gain~[1]", "live.gain~", 0 ],
			"parameterbanks" : 			{

			}
,
			"inherited_shortname" : 1
		}
,
		"dependency_cache" : [ 			{
				"name" : "percolate.jpg",
				"bootpath" : "~/Documents/Max Third Party Externals/dev/percolate/media",
				"patcherrelativepath" : "../media",
				"type" : "JPEG",
				"implicit" : 1
			}
, 			{
				"name" : "findtrigger~.maxpat",
				"bootpath" : "~/Documents/Max Third Party Externals/dev/percolate/help",
				"patcherrelativepath" : ".",
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
		"autosave" : 0
	}

}
