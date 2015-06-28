{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 7,
			"minor" : 0,
			"revision" : 4,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"rect" : [ 66.0, 95.0, 802.0, 612.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
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
		"boxes" : [ 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-51",
					"linecount" : 7,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 646.0, 359.0, 147.0, 112.0 ],
					"style" : "",
					"text" : "friggin' filter ratio (interpolates between the one-pole filter of the flute and the lowpass fliter of the plucked string. nutty."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-2",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 689.5, 61.0, 19.0, 23.0 ],
					"style" : "",
					"text" : "1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-3",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 687.5, 27.0, 75.5, 23.0 ],
					"style" : "",
					"text" : "loadbang"
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-4",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 593.909058, 404.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-5",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 54.0, 150.0, 41.0, 23.0 ],
					"style" : "",
					"text" : "clear"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-10",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 311.0, 192.0, 21.0, 21.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-11",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 311.0, 220.0, 36.0, 23.0 ],
					"style" : "",
					"text" : "gate"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-12",
					"maxclass" : "preset",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "preset", "int", "preset", "int" ],
					"patching_rect" : [ 689.5, 102.0, 41.0, 30.0 ],
					"preset_data" : [ 						{
							"number" : 1,
							"data" : [ 5, "obj-45", "live.gain~", "float", -23.31867, 5, "obj-35", "kslider", "int", 77, 5, "obj-34", "flonum", "float", 5.0, 5, "obj-33", "flonum", "float", 0.05, 5, "obj-32", "flonum", "float", 698.456482, 5, "obj-30", "number", "int", 0, 5, "obj-21", "flonum", "float", 0.13, 5, "obj-20", "flonum", "float", 2182.676514, 5, "obj-19", "flonum", "float", 1.05, 5, "obj-18", "flonum", "float", 0.31, 5, "obj-17", "flonum", "float", 0.78, 5, "obj-7", "flonum", "float", 0.53, 5, "obj-6", "flonum", "float", 0.17, 5, "obj-14", "flonum", "float", 0.48, 5, "obj-10", "toggle", "int", 1, 5, "obj-4", "flonum", "float", 1.0 ]
						}
, 						{
							"number" : 2,
							"data" : [ 5, "obj-45", "live.gain~", "float", -23.31867, 5, "obj-35", "kslider", "int", 77, 5, "obj-34", "flonum", "float", 0.0, 5, "obj-33", "flonum", "float", 0.0, 5, "obj-32", "flonum", "float", 698.456482, 5, "obj-30", "number", "int", 0, 5, "obj-21", "flonum", "float", 0.0, 5, "obj-20", "flonum", "float", 2182.676514, 5, "obj-19", "flonum", "float", 0.0, 5, "obj-18", "flonum", "float", 1.63, 5, "obj-17", "flonum", "float", 0.64, 5, "obj-7", "flonum", "float", 3.0, 5, "obj-6", "flonum", "float", 0.99, 5, "obj-14", "flonum", "float", 0.06, 5, "obj-10", "toggle", "int", 0, 5, "obj-4", "flonum", "float", 1.0 ]
						}
, 						{
							"number" : 3,
							"data" : [ 5, "<invalid>", "kslider", "int", 65, 5, "<invalid>", "number", "float", 0.0, 5, "obj-31", "number", "float", 0.0, 5, "<invalid>", "number", "float", 349.228241, 5, "obj-28", "number", "int", 0, 5, "<invalid>", "number", "float", 0.0, 5, "<invalid>", "number", "float", 132.0, 5, "<invalid>", "number", "float", 0.829999, 5, "<invalid>", "number", "float", 0.55, 5, "<invalid>", "number", "float", 0.22, 5, "<invalid>", "number", "float", 2.0, 5, "obj-15", "number", "float", 0.95, 5, "<invalid>", "number", "float", 0.63, 5, "obj-10", "toggle", "int", 0, 5, "obj-6", "number", "float", 1.0 ]
						}
, 						{
							"number" : 4,
							"data" : [ 5, "<invalid>", "kslider", "int", 72, 5, "<invalid>", "number", "float", 8.0, 5, "obj-31", "number", "float", 0.1, 5, "<invalid>", "number", "float", 523.25116, 5, "obj-28", "number", "int", 0, 5, "<invalid>", "number", "float", 0.0, 5, "<invalid>", "number", "float", 1635.159912, 5, "<invalid>", "number", "float", 0.82, 5, "<invalid>", "number", "float", 1.63, 5, "<invalid>", "number", "float", 0.64, 5, "<invalid>", "number", "float", 3.0, 5, "obj-15", "number", "float", 0.99, 5, "<invalid>", "number", "float", 0.06, 5, "obj-10", "toggle", "int", 1, 5, "obj-6", "number", "float", 1.0 ]
						}
, 						{
							"number" : 5,
							"data" : [ 5, "<invalid>", "kslider", "int", 43, 5, "<invalid>", "number", "float", 0.0, 5, "obj-31", "number", "float", 0.0, 5, "<invalid>", "number", "float", 97.998856, 5, "obj-28", "number", "int", 11, 5, "<invalid>", "number", "float", 0.0, 5, "<invalid>", "number", "float", 306.246429, 5, "<invalid>", "number", "float", 0.0, 5, "<invalid>", "number", "float", 0.37, 5, "<invalid>", "number", "float", 0.78, 5, "<invalid>", "number", "float", 5.0, 5, "obj-15", "number", "float", 3.409999, 5, "<invalid>", "number", "float", 0.0, 5, "obj-10", "toggle", "int", 1, 5, "obj-6", "number", "float", 1.0 ]
						}
, 						{
							"number" : 6,
							"data" : [ 5, "<invalid>", "kslider", "int", 47, 5, "<invalid>", "number", "float", 5.0, 5, "obj-31", "number", "float", 0.06, 5, "<invalid>", "number", "float", 123.470825, 5, "obj-28", "number", "int", 6, 5, "<invalid>", "number", "float", 0.130001, 5, "<invalid>", "number", "float", 42.0, 5, "<invalid>", "number", "float", 1.059998, 5, "<invalid>", "number", "float", 0.31, 5, "<invalid>", "number", "float", 0.78, 5, "<invalid>", "number", "float", 9.0, 5, "obj-15", "number", "float", 3.309998, 5, "<invalid>", "number", "float", 109.0, 5, "obj-10", "toggle", "int", 0, 5, "obj-6", "number", "float", -1.0 ]
						}
, 						{
							"number" : 7,
							"data" : [ 5, "<invalid>", "kslider", "int", 55, 5, "<invalid>", "number", "float", 5.0, 5, "obj-31", "number", "float", 0.06, 5, "<invalid>", "number", "float", 195.997711, 5, "obj-28", "number", "int", 6, 5, "<invalid>", "number", "float", 0.130001, 5, "<invalid>", "number", "float", 42.0, 5, "<invalid>", "number", "float", 1.059998, 5, "<invalid>", "number", "float", 0.31, 5, "<invalid>", "number", "float", 0.78, 5, "<invalid>", "number", "float", 9.0, 5, "obj-15", "number", "float", 3.309998, 5, "<invalid>", "number", "float", 109.0, 5, "obj-10", "toggle", "int", 0, 5, "obj-6", "number", "float", 0.02 ]
						}
, 						{
							"number" : 8,
							"data" : [ 5, "<invalid>", "kslider", "int", 43, 5, "<invalid>", "number", "float", 5.0, 5, "obj-31", "number", "float", 47.0, 5, "<invalid>", "number", "float", 97.998856, 5, "obj-28", "number", "int", 6, 5, "<invalid>", "number", "float", 0.130001, 5, "<invalid>", "number", "float", 42.0, 5, "<invalid>", "number", "float", 1.53, 5, "<invalid>", "number", "float", 0.059999, 5, "<invalid>", "number", "float", 0.78, 5, "<invalid>", "number", "float", 78.0, 5, "obj-15", "number", "float", 3.309998, 5, "<invalid>", "number", "float", 109.0, 5, "obj-10", "toggle", "int", 0, 5, "obj-6", "number", "float", 0.02 ]
						}
, 						{
							"number" : 9,
							"data" : [ 5, "<invalid>", "kslider", "int", 72, 5, "<invalid>", "number", "float", 0.0, 5, "obj-31", "number", "float", 0.0, 5, "<invalid>", "number", "float", 523.25116, 5, "obj-28", "number", "int", 0, 5, "<invalid>", "number", "float", 0.0, 5, "<invalid>", "number", "float", 1635.159912, 5, "<invalid>", "number", "float", 0.829999, 5, "<invalid>", "number", "float", 0.55, 5, "<invalid>", "number", "float", 0.22, 5, "<invalid>", "number", "float", 2.0, 5, "obj-15", "number", "float", 0.95, 5, "<invalid>", "number", "float", 0.63, 5, "obj-10", "toggle", "int", 1, 5, "obj-6", "number", "float", 1.0 ]
						}
, 						{
							"number" : 10,
							"data" : [ 5, "<invalid>", "kslider", "int", 84, 5, "<invalid>", "number", "float", 0.0, 5, "obj-31", "number", "float", 0.0, 5, "<invalid>", "number", "float", 1046.502319, 5, "obj-28", "number", "int", 0, 5, "<invalid>", "number", "float", 0.0, 5, "<invalid>", "number", "float", 3270.319824, 5, "<invalid>", "number", "float", 0.0, 5, "<invalid>", "number", "float", 1.63, 5, "<invalid>", "number", "float", 0.64, 5, "<invalid>", "number", "float", 3.0, 5, "obj-15", "number", "float", 2.0, 5, "<invalid>", "number", "float", 0.0, 5, "obj-10", "toggle", "int", 1, 5, "obj-6", "number", "float", 0.0 ]
						}
 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-13",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 402.0, 161.0, 38.0, 23.0 ],
					"style" : "",
					"text" : "mtof"
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-14",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 546.818176, 301.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-6",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 593.909058, 330.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-7",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 81.0, 239.5, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-17",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 94.0, 273.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-18",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 111.0, 303.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-19",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 131.0, 342.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-20",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 311.0, 281.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-21",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 499.727264, 161.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-24",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 646.0, 330.0, 140.0, 25.0 ],
					"style" : "",
					"text" : "Bore/distortion gain"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-25",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 601.5, 299.5, 129.0, 25.0 ],
					"style" : "",
					"text" : "jet/feedback coeff"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-26",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 554.5, 271.5, 118.0, 25.0 ],
					"style" : "",
					"text" : "Flute/string freq"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-27",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 560.5, 230.0, 76.0, 25.0 ],
					"style" : "",
					"text" : "vib amp"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-28",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 554.5, 192.0, 76.0, 25.0 ],
					"style" : "",
					"text" : "vib freq"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-29",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 67.0, 213.0, 86.0, 23.0 ],
					"style" : "",
					"text" : "prepend mic"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-30",
					"maxclass" : "number",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 67.0, 183.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-31",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 23.5, 152.0, 23.0, 23.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-32",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 499.727264, 273.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-33",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 499.727264, 230.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-34",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 499.727264, 195.0, 50.0, 22.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"blackkeycolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"hkeycolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ],
					"id" : "obj-35",
					"maxclass" : "kslider",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "int", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 23.5, 102.0, 294.0, 34.0 ],
					"presentation_rect" : [ 0.0, 0.0, 294.0, 35.0 ],
					"range" : 72,
					"style" : "",
					"whitekeycolor" : [ 1.0, 1.0, 1.0, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-36",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 554.5, 161.0, 87.0, 25.0 ],
					"style" : "",
					"text" : "noise gain"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-37",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 357.5, 281.0, 127.0, 25.0 ],
					"style" : "",
					"text" : "Jet/feedback freq"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-38",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 183.0, 342.0, 119.0, 25.0 ],
					"style" : "",
					"text" : "breath pressure"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-39",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 166.0, 303.0, 82.0, 25.0 ],
					"style" : "",
					"text" : "body size"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-40",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 154.0, 271.5, 106.0, 25.0 ],
					"style" : "",
					"text" : "pluck position"
				}

			}
, 			{
				"box" : 				{
					"color" : [ 0.8, 0.611765, 0.380392, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-44",
					"maxclass" : "newobj",
					"numinlets" : 12,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 25.0, 466.0, 537.0, 23.0 ],
					"style" : "",
					"text" : "blotar~"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-41",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 135.0, 238.0, 87.0, 25.0 ],
					"style" : "",
					"text" : "pluck amp"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-46",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 337.0, 190.0, 140.0, 25.0 ],
					"style" : "",
					"text" : "link with bore freq"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-47",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 311.0, 249.0, 51.0, 23.0 ],
					"style" : "",
					"text" : "/ 0.32"
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
					"patching_rect" : [ 25.0, 502.0, 136.0, 48.0 ],
					"presentation_rect" : [ 0.0, 0.0, 50.0, 48.0 ],
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
					"id" : "obj-9",
					"local" : 1,
					"maxclass" : "ezdac~",
					"numinlets" : 2,
					"numoutlets" : 0,
					"patching_rect" : [ 25.0, 560.0, 45.0, 45.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-22",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 4.0, 62.0, 558.0, 36.0 ],
					"style" : "",
					"text" : "flute-guitar hybrid model. Blotar~ is an example of what you can do with the synthesis toolkit. it's parameters morph between an electric guitar model and a flute.",
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
					"patching_rect" : [ 4.0, 3.0, 212.0, 60.0 ],
					"style" : "",
					"text" : "blowtar~",
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
					"patching_rect" : [ 656.5, 476.0, 140.0, 87.0 ],
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
					"patching_rect" : [ 421.5, 572.0, 375.0, 21.0 ],
					"style" : "",
					"text" : "• by dan trueman, computer music center, columbia university..."
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-11", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-10", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-47", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-11", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-11", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-32", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 9 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-17", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-18", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 3 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-19", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-2", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-20", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-21", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-29", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-29", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-30", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-31", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 8 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-32", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 7 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-33", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 6 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-13", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-35", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-31", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-35", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 11 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-45", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-44", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-45", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-45", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-47", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 10 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-6", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-7", 0 ]
				}

			}
 ],
		"parameters" : 		{
			"obj-45" : [ "live.gain~", "live.gain~", 0 ]
		}
,
		"dependency_cache" : [ 			{
				"name" : "percolate.jpg",
				"bootpath" : "/Users/Shared/Max 7/Packages/PeRColate/media",
				"type" : "JPEG",
				"implicit" : 1
			}
, 			{
				"name" : "blotar~.mxo",
				"type" : "iLaX"
			}
 ],
		"embedsnapshot" : 0
	}

}
