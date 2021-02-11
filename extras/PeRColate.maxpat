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
		"rect" : [ 53.0, 96.0, 535.0, 530.0 ],
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
		"title" : "overview",
		"boxes" : [ 			{
				"box" : 				{
					"bgcolor" : [ 0.156862745098039, 0.156862745098039, 0.156862745098039, 1.0 ],
					"fontname" : "Lato",
					"id" : "obj-59",
					"maxclass" : "textbutton",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 41.118113160133362, 448.140216120237596, 184.0, 35.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 24.118113160133362, 399.803381550725476, 184.0, 35.0 ],
					"rounded" : 8.0,
					"text" : "Miscellaneous",
					"texton" : "Miscellaneous",
					"textoncolor" : [ 0.839216, 0.882353, 0.886275, 1.0 ],
					"truncate" : 0
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-58",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 8,
							"minor" : 2,
							"revision" : 0,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ 328.0, 210.0, 319.0, 285.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 2,
						"gridsize" : [ 10.0, 10.0 ],
						"gridsnaponopen" : 2,
						"objectsnaponopen" : 0,
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
						"style" : "Audiomix",
						"subpatcher_template" : "AudioMix Template",
						"assistshowspatchername" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"id" : "obj-16",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 180.0, 170.0, 82.0, 20.0 ],
									"text" : "Format name"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-13",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 100.0, 220.0, 70.0, 20.0 ],
									"text" : "Load patch"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-11",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 190.0, 140.0, 99.0, 20.0 ],
									"text" : "Remove slashes"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-10",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 170.0, 110.0, 97.0, 20.0 ],
									"text" : "Remove spaces"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-8",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 120.0, 80.0, 70.0, 20.0 ],
									"text" : "Remove \" \""
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-6",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 80.0, 30.0, 70.0, 33.0 ],
									"text" : "Text from textbutton"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-3",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 190.0, 219.0, 22.0 ],
									"text" : "sprintf loadunique percolate.%s.maxpat"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-2",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 5,
									"outlettype" : [ "", "", "", "", "" ],
									"patching_rect" : [ 40.0, 140.0, 141.0, 22.0 ],
									"text" : "regexp / @substitute %0"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-7",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 110.0, 125.0, 22.0 ],
									"text" : "tosymbol @separator"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-1",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 80.0, 73.0, 22.0 ],
									"text" : "fromsymbol"
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-12",
									"index" : 1,
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 30.0, 30.0, 30.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-14",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 220.0, 53.0, 22.0 ],
									"text" : "pcontrol"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-7", 0 ],
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"source" : [ "obj-12", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"source" : [ "obj-2", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"source" : [ "obj-2", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-14", 0 ],
									"source" : [ "obj-3", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-2", 0 ],
									"source" : [ "obj-7", 0 ]
								}

							}
 ],
						"styles" : [ 							{
								"name" : "Audiomix",
								"default" : 								{
									"bgfillcolor" : 									{
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
, 							{
								"name" : "Max 12 Regular",
								"parentstyle" : "",
								"multi" : 0
							}
 ]
					}
,
					"patching_rect" : [ 56.118113160133362, 582.0, 47.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"globalpatchername" : "",
						"style" : "Audiomix",
						"tags" : ""
					}
,
					"text" : "p Load"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.294117647058824, 0.584313725490196, 0.694117647058824, 1.0 ],
					"fontname" : "Lato",
					"id" : "obj-50",
					"maxclass" : "textbutton",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 33.118113160133362, 493.800252437591553, 184.0, 35.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 24.118113160133362, 473.955584116930254, 77.0, 35.0 ],
					"rounded" : 8.0,
					"text" : "About",
					"texton" : "About",
					"textoncolor" : [ 0.929411764705882, 0.941176470588235, 0.956862745098039, 1.0 ],
					"truncate" : 0
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.156862745098039, 0.156862745098039, 0.156862745098039, 1.0 ],
					"fontname" : "Lato",
					"id" : "obj-41",
					"maxclass" : "textbutton",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 352.118113160133362, 469.800252437591553, 184.0, 35.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 299.618113160133362, 473.955584116930254, 184.0, 35.0 ],
					"rounded" : 8.0,
					"text" : "Audio FX",
					"texton" : "Audio FX",
					"textoncolor" : [ 0.839216, 0.882353, 0.886275, 1.0 ],
					"truncate" : 0
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.156862745098039, 0.156862745098039, 0.156862745098039, 1.0 ],
					"fontname" : "Lato",
					"id" : "obj-40",
					"maxclass" : "textbutton",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 33.118113160133362, 425.343243258095299, 184.0, 35.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 24.118113160133362, 350.762590193103506, 184.0, 35.0 ],
					"rounded" : 8.0,
					"text" : "String and Hybrid",
					"texton" : "String and Hybrid",
					"textoncolor" : [ 0.839216, 0.882353, 0.886275, 1.0 ],
					"truncate" : 0
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.156862745098039, 0.156862745098039, 0.156862745098039, 1.0 ],
					"fontname" : "Lato",
					"id" : "obj-39",
					"maxclass" : "textbutton",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 33.118113160133362, 372.207495552969363, 184.0, 35.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 24.118113160133362, 301.721798835481536, 184.0, 35.0 ],
					"rounded" : 8.0,
					"text" : "Wind Instruments",
					"texton" : "Wind Instruments",
					"textoncolor" : [ 0.839216, 0.882353, 0.886275, 1.0 ],
					"truncate" : 0
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.156862745098039, 0.156862745098039, 0.156862745098039, 1.0 ],
					"fontname" : "Lato",
					"id" : "obj-37",
					"maxclass" : "textbutton",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 33.118113160133362, 265.936000142717489, 184.0, 35.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 24.118113160133362, 203.640216120237596, 184.0, 35.0 ],
					"rounded" : 8.0,
					"text" : "Shakers",
					"texton" : "Shakers",
					"textoncolor" : [ 0.839216, 0.882353, 0.886275, 1.0 ],
					"truncate" : 0
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.156862745098039, 0.156862745098039, 0.156862745098039, 1.0 ],
					"fontname" : "Lato",
					"id" : "obj-36",
					"maxclass" : "textbutton",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 33.118113160133362, 212.800252437591553, 184.0, 35.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 24.118113160133362, 252.681007477859566, 184.0, 35.0 ],
					"rounded" : 8.0,
					"text" : "Pitched Percussion",
					"texton" : "Pitched Percussion",
					"textoncolor" : [ 0.839216, 0.882353, 0.886275, 1.0 ],
					"truncate" : 0
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.156862745098039, 0.156862745098039, 0.156862745098039, 1.0 ],
					"fontname" : "Lato",
					"id" : "obj-35",
					"maxclass" : "textbutton",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 352.118113160133362, 326.800252437591553, 184.0, 35.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 299.618113160133362, 321.800252437591553, 184.0, 35.0 ],
					"rounded" : 8.0,
					"text" : "Generators",
					"texton" : "Generators",
					"textoncolor" : [ 0.839216, 0.882353, 0.886275, 1.0 ],
					"truncate" : 0
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.156862745098039, 0.156862745098039, 0.156862745098039, 1.0 ],
					"fontname" : "Lato",
					"id" : "obj-31",
					"maxclass" : "textbutton",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 352.118113160133362, 189.800252437591553, 184.0, 35.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 299.618113160133362, 178.800252437591553, 184.0, 35.0 ],
					"rounded" : 8.0,
					"text" : "Utilities",
					"texton" : "Utilities",
					"textoncolor" : [ 0.839216, 0.882353, 0.886275, 1.0 ],
					"truncate" : 0
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"id" : "obj-25",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 346.118113160133362, 414.984884440898895, 218.0, 50.0 ],
					"presentation" : 1,
					"presentation_linecount" : 3,
					"presentation_rect" : [ 293.618113160133362, 419.140216120237596, 218.0, 50.0 ],
					"text" : "From simple chorus and reverb effects to wild granulators, delay-line scrubbers, and more."
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"id" : "obj-24",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 346.118113160133362, 147.677164435386658, 215.0, 35.0 ],
					"presentation" : 1,
					"presentation_linecount" : 2,
					"presentation_rect" : [ 293.618113160133362, 136.677164435386658, 215.0, 35.0 ],
					"text" : "Signal rate tools for randomizing, comparing, inverting, and more."
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"id" : "obj-22",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 346.118113160133362, 272.984884440898895, 215.0, 50.0 ],
					"presentation" : 1,
					"presentation_linecount" : 3,
					"presentation_rect" : [ 293.618113160133362, 267.984884440898895, 215.0, 50.0 ],
					"text" : "Function generators and wavetable tools based on the work of Brad Garton and Dave Topper on RTcmix."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Futura Bold",
					"fontsize" : 18.0,
					"id" : "obj-21",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 346.118113160133362, 240.984884440898895, 203.0, 30.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 293.618113160133362, 235.984884440898895, 203.0, 30.0 ],
					"text" : "Function Generators"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Futura Bold",
					"fontsize" : 18.0,
					"id" : "obj-20",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 346.118113160133362, 382.984884440898895, 96.0, 30.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 293.618113160133362, 387.140216120237596, 96.0, 30.0 ],
					"text" : "Audio FX"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Futura Bold",
					"fontsize" : 18.0,
					"id" : "obj-19",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 346.118113160133362, 119.0, 196.0, 30.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 293.618113160133362, 108.0, 196.0, 30.0 ],
					"text" : "Signal Rate Utilities"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-18",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 29.5, 147.677164435386658, 216.0, 50.0 ],
					"presentation" : 1,
					"presentation_linecount" : 3,
					"presentation_rect" : [ 20.5, 137.677164435386658, 214.0, 50.0 ],
					"text" : "Physically modeled instruments ported from the Synthesis Toolkit (STK) by Perry Cook and Gary Scavone."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Futura Bold",
					"fontsize" : 18.0,
					"id" : "obj-15",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 29.5, 119.0, 162.0, 30.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 20.5, 109.0, 162.0, 30.0 ],
					"text" : "Physical Models"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Lato Medium Italic",
					"id" : "obj-8",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 287.118113160133362, 21.5, 233.0, 50.0 ],
					"presentation" : 1,
					"presentation_linecount" : 3,
					"presentation_rect" : [ 287.118113160133362, 21.5, 233.0, 50.0 ],
					"text" : "by Dan Trueman and R. Luke DuBois\nComputer Music Center\nColumbia University in the City of New York"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 1,
					"fontname" : "Futura Bold",
					"fontsize" : 48.0,
					"id" : "obj-4",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 7.5, 12.0, 268.0, 69.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 7.5, 12.0, 268.0, 69.0 ],
					"text" : "PeRColate"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-58", 0 ],
					"source" : [ "obj-31", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-58", 0 ],
					"source" : [ "obj-35", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-58", 0 ],
					"source" : [ "obj-36", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-58", 0 ],
					"source" : [ "obj-37", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-58", 0 ],
					"source" : [ "obj-39", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-58", 0 ],
					"source" : [ "obj-40", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-58", 0 ],
					"source" : [ "obj-41", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-58", 0 ],
					"source" : [ "obj-50", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-58", 0 ],
					"source" : [ "obj-59", 1 ]
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
