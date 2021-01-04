{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 8,
			"minor" : 1,
			"revision" : 8,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"classnamespace" : "box",
		"rect" : [ -2113.0, 21.0, 689.0, 379.0 ],
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
		"showontab" : 1,
		"assistshowspatchername" : 0,
		"title" : "overview",
		"boxes" : [ 			{
				"box" : 				{
					"id" : "obj-113",
					"linecount" : 4,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 27.0, 270.866156101226807, 305.905520081520081, 60.0 ],
					"text" : "Credits:\n\nDan Trueman and R. Luke DuBois (Computer Music Center, Columbia University in the City of New York)"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-111",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 8,
							"minor" : 1,
							"revision" : 8,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ 0.0, 26.0, 689.0, 353.0 ],
						"bglocked" : 0,
						"openinpresentation" : 1,
						"default_fontsize" : 12.0,
						"default_fontface" : 2,
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
						"showontab" : 1,
						"assistshowspatchername" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-198",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.200000083446504, 364.400004029273987, 64.0, 24.0 ],
									"text" : "pcontrol"
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-199",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.200000083446504, 331.400004029273987, 59.0, 24.0 ],
									"text" : "help $1"
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-200",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.200000083446504, 300.400004029273987, 116.0, 24.0 ],
									"text" : "prepend symbol"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-50",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 3.200000107288361, 36.400000095367432, 150.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 1.999999761581421, 36.400000095367432, 150.0, 20.0 ],
									"text" : "Some other stuff"
								}

							}
, 							{
								"box" : 								{
									"fontface" : 1,
									"fontsize" : 18.0,
									"id" : "obj-48",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 3.200000107288361, 4.399999618530273, 226.0, 27.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 1.999999761581421, 4.399999618530273, 226.0, 27.0 ],
									"text" : "Synthesis isn't dead..."
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"id" : "obj-27",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 403.800004541873932, 219.739333155312352, 134.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 387.000004291534424, 215.739333095707707, 134.0, 20.0 ],
									"style" : "default",
									"text" : "voice formant synthesis"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgcolor2" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.415686274509804, 0.415686274509804, 0.694117647058824, 1.0 ],
									"bgfillcolor_color1" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"fontface" : 0,
									"gradient" : 1,
									"id" : "obj-28",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 313.600004470348381, 217.584616805956841, 87.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 296.800004220008873, 213.584616746352197, 87.0, 22.0 ],
									"style" : "default",
									"text" : "voice_form~"
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"id" : "obj-29",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 403.800004541873932, 189.976082080893434, 84.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 387.000004291534424, 185.976082021288789, 84.0, 20.0 ],
									"style" : "default",
									"text" : "some FM stuff"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgcolor2" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.415686274509804, 0.415686274509804, 0.694117647058824, 1.0 ],
									"bgfillcolor_color1" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"fontface" : 0,
									"gradient" : 1,
									"id" : "obj-30",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 313.600004470348381, 188.507693623579428, 63.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 296.800004220008873, 184.507693563974783, 63.0, 22.0 ],
									"style" : "default",
									"text" : "prc_fm~"
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"id" : "obj-72",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 403.800004541873932, 160.212831006474545, 135.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 387.000004291534424, 156.2128309468699, 135.0, 20.0 ],
									"style" : "default",
									"text" : "sub-harmonic oscillator"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgcolor2" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.415686274509804, 0.415686274509804, 0.694117647058824, 1.0 ],
									"bgfillcolor_color1" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"fontface" : 0,
									"gradient" : 1,
									"id" : "obj-73",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 313.600004470348381, 159.430770441201958, 54.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 296.800004220008873, 155.430770381597313, 54.0, 22.0 ],
									"style" : "default",
									"text" : "weave~"
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"id" : "obj-74",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 403.800004541873932, 130.449579932055656, 98.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 387.000004291534424, 126.449579872451011, 98.0, 20.0 ],
									"style" : "default",
									"text" : "signal crossover"
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"id" : "obj-75",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 403.800004541873932, 100.686328857636738, 147.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 387.000004291534424, 96.686328798032093, 147.0, 20.0 ],
									"style" : "default",
									"text" : "linear wave-terrain model"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgcolor2" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.415686274509804, 0.415686274509804, 0.694117647058824, 1.0 ],
									"bgfillcolor_color1" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"fontface" : 0,
									"gradient" : 1,
									"id" : "obj-76",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 313.600004470348381, 130.353847258824544, 55.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 296.800004220008873, 126.353847199219899, 55.0, 22.0 ],
									"style" : "default",
									"text" : "waffle~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgcolor2" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.415686274509804, 0.415686274509804, 0.694117647058824, 1.0 ],
									"bgfillcolor_color1" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"fontface" : 0,
									"gradient" : 1,
									"id" : "obj-77",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 313.600004470348381, 101.276924076447088, 59.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 296.800004220008873, 97.276924016842443, 59.0, 22.0 ],
									"style" : "default",
									"text" : "terrain~"
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"id" : "obj-91",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 403.800004541873932, 70.923077783217835, 208.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 387.000004291534424, 66.92307772361319, 208.0, 20.0 ],
									"style" : "default",
									"text" : "audio-rate random number generator"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgcolor2" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.415686274509804, 0.415686274509804, 0.694117647058824, 1.0 ],
									"bgfillcolor_color1" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"fontface" : 0,
									"gradient" : 1,
									"id" : "obj-92",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 313.600004470348381, 72.200000894069674, 58.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 296.800004220008873, 68.20000083446503, 58.0, 22.0 ],
									"style" : "default",
									"text" : "random~"
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"id" : "obj-139",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 89.399999856948853, 249.532426108134075, 131.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 80.599999725818634, 245.53242604852943, 131.0, 20.0 ],
									"style" : "default",
									"text" : "reverses sample order"
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"id" : "obj-140",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 89.399999856948853, 219.977021905790025, 106.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 80.599999725818634, 215.97702184618538, 106.0, 20.0 ],
									"style" : "default",
									"text" : "signal randomizer"
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"id" : "obj-141",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 89.399999856948853, 190.421617703445975, 86.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 80.599999725818634, 186.42161764384133, 86.0, 20.0 ],
									"style" : "default",
									"text" : "signal inverter"
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"id" : "obj-142",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 89.399999856948853, 160.866213501101868, 87.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 80.599999725818634, 156.866213441497223, 87.0, 20.0 ],
									"style" : "default",
									"text" : "signal rounder"
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"id" : "obj-143",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 89.399999856948853, 131.310809298757817, 163.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 80.599999725818634, 127.310809239153173, 163.0, 20.0 ],
									"style" : "default",
									"text" : "three-way signal comparator"
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"id" : "obj-144",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 89.399999856948853, 101.755405096413753, 80.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 80.599999725818634, 97.755405036809108, 80.0, 20.0 ],
									"style" : "default",
									"text" : "close to zero"
								}

							}
, 							{
								"box" : 								{
									"fontface" : 0,
									"id" : "obj-145",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 89.399999856948853, 72.200000894069674, 80.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 80.599999725818634, 68.20000083446503, 80.0, 20.0 ],
									"style" : "default",
									"text" : "far from zero"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgcolor2" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.415686274509804, 0.415686274509804, 0.694117647058824, 1.0 ],
									"bgfillcolor_color1" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"fontface" : 0,
									"gradient" : 1,
									"id" : "obj-165",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.200000083446504, 246.661539988334368, 44.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 10.399999952316286, 242.661539928729724, 44.0, 22.0 ],
									"style" : "default",
									"text" : "klutz~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgcolor2" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.415686274509804, 0.415686274509804, 0.694117647058824, 1.0 ],
									"bgfillcolor_color1" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"fontface" : 0,
									"gradient" : 1,
									"id" : "obj-166",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.200000083446504, 217.584616805956898, 48.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 10.399999952316286, 213.584616746352253, 48.0, 22.0 ],
									"style" : "default",
									"text" : "jitter~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgcolor2" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.415686274509804, 0.415686274509804, 0.694117647058824, 1.0 ],
									"bgfillcolor_color1" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"fontface" : 0,
									"gradient" : 1,
									"id" : "obj-167",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.200000083446504, 188.507693623579428, 36.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 10.399999952316286, 184.507693563974783, 36.0, 22.0 ],
									"style" : "default",
									"text" : "flip~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgcolor2" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.415686274509804, 0.415686274509804, 0.694117647058824, 1.0 ],
									"bgfillcolor_color1" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"fontface" : 0,
									"gradient" : 1,
									"id" : "obj-168",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.200000083446504, 159.430770441202014, 44.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 10.399999952316286, 155.43077038159737, 44.0, 22.0 ],
									"style" : "default",
									"text" : "escal~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgcolor2" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.415686274509804, 0.415686274509804, 0.694117647058824, 1.0 ],
									"bgfillcolor_color1" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"fontface" : 0,
									"gradient" : 1,
									"id" : "obj-169",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.200000083446504, 130.353847258824572, 50.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 10.399999952316286, 126.353847199219928, 50.0, 22.0 ],
									"style" : "default",
									"text" : "chase~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgcolor2" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.415686274509804, 0.415686274509804, 0.694117647058824, 1.0 ],
									"bgfillcolor_color1" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"fontface" : 0,
									"gradient" : 1,
									"id" : "obj-170",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.200000083446504, 101.276924076447131, 57.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 10.399999952316286, 97.276924016842486, 57.0, 22.0 ],
									"style" : "default",
									"text" : "absmin~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgcolor2" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.415686274509804, 0.415686274509804, 0.694117647058824, 1.0 ],
									"bgfillcolor_color1" : [ 0.6, 0.6, 1.0, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"fontface" : 0,
									"gradient" : 1,
									"id" : "obj-171",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.200000083446504, 72.200000894069674, 63.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 10.399999952316286, 68.20000083446503, 63.0, 22.0 ],
									"style" : "default",
									"text" : "absmax~"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-165", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-166", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-167", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-168", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-169", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-170", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-171", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-198", 0 ],
									"hidden" : 1,
									"source" : [ "obj-199", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-199", 0 ],
									"hidden" : 1,
									"source" : [ "obj-200", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-28", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-30", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-73", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-76", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-77", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-92", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 634.857694566249847, 160.984884440898895, 141.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"fontface" : 2,
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p \"synthesis isn't dead...\""
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-110",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 8,
							"minor" : 1,
							"revision" : 8,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ 0.0, 26.0, 689.0, 353.0 ],
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
						"showontab" : 1,
						"assistshowspatchername" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-198",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 11.800000131130219, 409.400004923343658, 64.0, 24.0 ],
									"text" : "pcontrol"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-199",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 11.800000131130219, 376.400004923343658, 59.0, 24.0 ],
									"text" : "help $1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-200",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 11.800000131130219, 345.400004923343658, 116.0, 24.0 ],
									"text" : "prepend symbol"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-50",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 3.0, 37.0, 150.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 3.0, 37.0, 150.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontface" : 1,
									"fontsize" : 18.0,
									"id" : "obj-48",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 3.0, 5.0, 226.0, 27.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 3.0, 5.0, 226.0, 27.0 ],
									"text" : "MaxGens"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-60",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 62.800000131130219, 132.200000911951065, 240.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 72.400000274181366, 123.400000780820847, 177.0, 20.0 ],
									"style" : "default",
									"text" : "sinusoidal wavetable generator."
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-61",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 62.800000131130219, 102.000000759959221, 239.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 72.400000274181366, 93.200000628829002, 125.0, 20.0 ],
									"style" : "default",
									"text" : "linear b.p.f. generator."
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-62",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 62.800000131130219, 71.800000607967377, 240.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 72.400000274181366, 63.000000476837158, 157.0, 20.0 ],
									"style" : "default",
									"text" : "exponential b.p.f. generator."
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgcolor2" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.32156862745098, 0.517647058823529, 0.517647058823529, 1.0 ],
									"bgfillcolor_color1" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-63",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 11.800000131130219, 131.000000849366188, 35.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 21.400000274181366, 122.20000071823597, 35.0, 22.0 ],
									"style" : "default",
									"text" : "gen9"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgcolor2" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.32156862745098, 0.517647058823529, 0.517647058823529, 1.0 ],
									"bgfillcolor_color1" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-64",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 11.800000131130219, 100.900000728666782, 35.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 21.400000274181366, 92.100000597536564, 35.0, 22.0 ],
									"style" : "default",
									"text" : "gen7"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgcolor2" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.32156862745098, 0.517647058823529, 0.517647058823529, 1.0 ],
									"bgfillcolor_color1" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-65",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 11.800000131130219, 70.800000607967377, 35.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 21.400000274181366, 62.000000476837158, 35.0, 22.0 ],
									"style" : "default",
									"text" : "gen5"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-89",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 62.800000131130219, 283.200001671910286, 242.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 370.800004720687866, 155.000001057982445, 242.0, 20.0 ],
									"style" : "default",
									"text" : "hamming/hanning function generator."
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgcolor2" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.32156862745098, 0.517647058823529, 0.517647058823529, 1.0 ],
									"bgfillcolor_color1" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-90",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 11.800000131130219, 281.500001452863216, 44.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 319.800004720687866, 153.300000838935375, 44.0, 22.0 ],
									"style" : "default",
									"text" : "gen25"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-146",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 62.800000131130219, 253.000001519918442, 239.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 370.800004720687866, 124.800000905990601, 239.0, 20.0 ],
									"style" : "default",
									"text" : "breakpoint function generator."
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-147",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 62.800000131130219, 222.800001367926598, 240.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 370.800004720687866, 94.600000753998756, 240.0, 20.0 ],
									"style" : "default",
									"text" : "random function generator."
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-148",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 62.800000131130219, 192.600001215934753, 240.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 370.800004720687866, 64.400000602006912, 240.0, 20.0 ],
									"style" : "default",
									"text" : "solves chebyshev polynomials."
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-149",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 62.800000131130219, 162.400001063942909, 241.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 72.400000274181366, 153.600000932812691, 184.0, 20.0 ],
									"style" : "default",
									"text" : "computes a harmonic wavetable."
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgcolor2" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.32156862745098, 0.517647058823529, 0.517647058823529, 1.0 ],
									"bgfillcolor_color1" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-173",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 11.800000131130219, 251.400001332163811, 44.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 319.800004720687866, 123.20000071823597, 44.0, 22.0 ],
									"style" : "default",
									"text" : "gen24"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgcolor2" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.32156862745098, 0.517647058823529, 0.517647058823529, 1.0 ],
									"bgfillcolor_color1" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-174",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 11.800000131130219, 221.300001211464405, 44.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 319.800004720687866, 93.100000597536564, 44.0, 22.0 ],
									"style" : "default",
									"text" : "gen20"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgcolor2" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.32156862745098, 0.517647058823529, 0.517647058823529, 1.0 ],
									"bgfillcolor_color1" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-175",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 11.800000131130219, 191.200001090764999, 44.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 319.800004720687866, 63.000000476837158, 44.0, 22.0 ],
									"style" : "default",
									"text" : "gen17"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgcolor2" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.32156862745098, 0.517647058823529, 0.517647058823529, 1.0 ],
									"bgfillcolor_color1" : [ 0.380392156862745, 0.611764705882353, 0.611764705882353, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-176",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 11.800000131130219, 161.100000970065594, 44.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 21.400000274181366, 152.300000838935375, 44.0, 22.0 ],
									"style" : "default",
									"text" : "gen10"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-173", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-174", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-175", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-176", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-198", 0 ],
									"hidden" : 1,
									"source" : [ "obj-199", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-199", 0 ],
									"hidden" : 1,
									"source" : [ "obj-200", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-63", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-64", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-65", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-90", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 623.319232642650604, 102.861796438694, 70.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p MaxGens"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-109",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 8,
							"minor" : 1,
							"revision" : 8,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ 0.0, 26.0, 689.0, 353.0 ],
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
						"showontab" : 1,
						"assistshowspatchername" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-198",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.599999845027924, 434.800005078315735, 64.0, 24.0 ],
									"text" : "pcontrol"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-199",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.599999845027924, 401.800005078315735, 59.0, 24.0 ],
									"text" : "help $1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-200",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.599999845027924, 370.800005078315735, 116.0, 24.0 ],
									"text" : "prepend symbol"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-3",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 18.0, 52.0, 150.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 2.79999977350235, 36.79999977350235, 150.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontface" : 1,
									"fontsize" : 18.0,
									"id" : "obj-48",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 18.0, 20.0, 226.0, 27.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 2.79999977350235, 4.79999977350235, 226.0, 27.0 ],
									"text" : "Random DSP"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-1",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 415.600004613399506, 328.880001711845409, 207.000000476837158, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 417.200004637241364, 306.480001378059399, 207.000000476837158, 20.0 ],
									"style" : "default",
									"text" : "output greatest N samples in a vector"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.203921568627451, 0.435294117647059, 0.270588235294118, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-2",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 325.800004422664642, 327.160001432895683, 47.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 327.4000044465065, 304.760001099109672, 47.0, 22.0 ],
									"style" : "default",
									"text" : "casey~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-5",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 415.600004613399506, 302.160001611709617, 164.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 417.200004637241364, 279.760001277923607, 164.0, 20.0 ],
									"style" : "default",
									"text" : "bin specific fft bin compander"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.203921568627451, 0.435294117647059, 0.270588235294118, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-6",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 325.800004422664642, 300.520001363754261, 78.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 327.4000044465065, 278.12000102996825, 78.0, 22.0 ],
									"style" : "default",
									"text" : "vcompand2~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-7",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 415.600004613399506, 275.440001511573769, 101.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 417.200004637241364, 253.040001177787758, 101.0, 20.0 ],
									"style" : "default",
									"text" : "fft bin compander"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.203921568627451, 0.435294117647059, 0.270588235294118, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-8",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 325.800004422664642, 273.880001294612896, 71.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 327.4000044465065, 251.480000960826885, 71.0, 22.0 ],
									"style" : "default",
									"text" : "vcompand~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-9",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 415.600004613399506, 248.720001411437977, 78.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 417.200004637241364, 226.320001077651966, 78.0, 20.0 ],
									"style" : "default",
									"text" : "fft bin warper"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.203921568627451, 0.435294117647059, 0.270588235294118, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-10",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 325.800004422664642, 247.240001225471502, 48.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 327.4000044465065, 224.840000891685492, 48.0, 22.0 ],
									"style" : "default",
									"text" : "vwarp~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-11",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 415.600004613399506, 222.000001311302185, 88.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 417.200004637241364, 199.600000977516174, 88.0, 20.0 ],
									"style" : "default",
									"text" : "fft bin stretcher"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.203921568627451, 0.435294117647059, 0.270588235294118, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-12",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 325.800004422664642, 220.600001156330109, 58.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 327.4000044465065, 198.200000822544098, 58.0, 22.0 ],
									"style" : "default",
									"text" : "vstretch~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-13",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 415.600004613399506, 195.280001211166393, 164.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 417.200004637241364, 172.880000877380382, 164.0, 20.0 ],
									"style" : "default",
									"text" : "mesh2D~ can also be a filter!"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.203921568627451, 0.435294117647059, 0.270588235294118, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-14",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 325.800004422664642, 193.960001087188715, 60.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 327.4000044465065, 171.560000753402704, 60.0, 22.0 ],
									"style" : "default",
									"text" : "mesh2D~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-15",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 415.600004613399506, 168.560001111030573, 93.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 417.200004637241364, 146.160000777244562, 93.0, 20.0 ],
									"style" : "default",
									"text" : "simple choruser"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.203921568627451, 0.435294117647059, 0.270588235294118, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-16",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 325.800004422664642, 167.320001018047321, 75.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 327.4000044465065, 144.920000684261311, 75.0, 22.0 ],
									"style" : "default",
									"text" : "prc_chorus~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-17",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 415.600004613399506, 141.840001010894781, 108.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 417.200004637241364, 119.44000067710877, 108.0, 20.0 ],
									"style" : "default",
									"text" : "simple pitch shifter"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.203921568627451, 0.435294117647059, 0.270588235294118, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-18",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 325.800004422664642, 140.680000948905956, 57.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 327.4000044465065, 118.280000615119945, 57.0, 22.0 ],
									"style" : "default",
									"text" : "pit_shift~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-19",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 415.600004613399506, 115.120000910758975, 152.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 417.200004637241364, 92.720000576972964, 152.0, 20.0 ],
									"style" : "default",
									"text" : "Perry's simple reverberator"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.203921568627451, 0.435294117647059, 0.270588235294118, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-20",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 325.800004422664642, 114.040000879764563, 64.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 327.4000044465065, 91.640000545978552, 64.0, 22.0 ],
									"style" : "default",
									"text" : "PRC_rev~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-21",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 415.600004613399506, 88.400000810623169, 121.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 417.200004637241364, 66.000000476837158, 121.0, 20.0 ],
									"style" : "default",
									"text" : "CCRMA reverberator"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.203921568627451, 0.435294117647059, 0.270588235294118, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-22",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 325.800004422664642, 87.400000810623169, 48.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 327.4000044465065, 65.000000476837158, 48.0, 22.0 ],
									"style" : "default",
									"text" : "N_rev~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-23",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 110.800000071525574, 327.600001752376556, 131.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 112.400000095367432, 305.200001418590546, 131.0, 20.0 ],
									"style" : "default",
									"text" : "Chowning reverberator"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.203921568627451, 0.435294117647059, 0.270588235294118, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-24",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.399999856948853, 326.160001462698006, 54.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 20.99999988079071, 303.760001128911995, 54.0, 22.0 ],
									"style" : "default",
									"text" : "JC_rev~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-25",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 110.800000071525574, 300.400001645088196, 161.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 112.400000095367432, 278.000001311302185, 161.0, 20.0 ],
									"style" : "default",
									"text" : "for smoothing control signals"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.203921568627451, 0.435294117647059, 0.270588235294118, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-26",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.399999856948853, 299.120001387596119, 84.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 20.99999988079071, 276.720001053810108, 84.0, 22.0 ],
									"style" : "default",
									"text" : "curvesmooth~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-49",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 110.800000071525574, 273.200001537799835, 166.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 112.400000095367432, 250.800001204013824, 166.0, 20.0 ],
									"style" : "default",
									"text" : "like scrub~, but with feedback"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.203921568627451, 0.435294117647059, 0.270588235294118, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-50",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.399999856948853, 272.080001312494289, 48.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 20.99999988079071, 249.680000978708279, 48.0, 22.0 ],
									"style" : "default",
									"text" : "scrubf~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-51",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 110.800000071525574, 246.000001430511475, 171.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 112.400000095367432, 223.600001096725464, 171.0, 20.0 ],
									"style" : "default",
									"text" : "like record~, but with feedback"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.203921568627451, 0.435294117647059, 0.270588235294118, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-52",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.399999856948853, 245.040001237392431, 53.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 20.99999988079071, 222.64000090360642, 53.0, 22.0 ],
									"style" : "default",
									"text" : "recordf~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-53",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 110.800000071525574, 218.800001323223114, 203.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 112.400000095367432, 196.400000989437103, 203.0, 20.0 ],
									"style" : "default",
									"text" : "directional impulse response models"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.203921568627451, 0.435294117647059, 0.270588235294118, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-54",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.399999856948853, 218.000001162290573, 48.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 20.99999988079071, 195.600000828504562, 48.0, 22.0 ],
									"style" : "default",
									"text" : "nbody~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-56",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 110.800000071525574, 191.600001215934753, 173.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 112.400000095367432, 169.200000882148743, 173.0, 20.0 ],
									"style" : "default",
									"text" : "a triggered delay-line scrubber"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.203921568627451, 0.435294117647059, 0.270588235294118, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-57",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.399999856948853, 190.960001087188715, 52.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 20.99999988079071, 168.560000753402704, 52.0, 22.0 ],
									"style" : "default",
									"text" : "flapper~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-80",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 110.800000071525574, 110.000000894069672, 71.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 112.400000095367432, 87.600000560283661, 71.0, 20.0 ],
									"style" : "default",
									"text" : "stereo filter"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.203921568627451, 0.435294117647059, 0.270588235294118, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-81",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.399999856948853, 109.840000861883169, 32.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 20.99999988079071, 87.440000528097158, 32.0, 22.0 ],
									"style" : "default",
									"text" : "gQ~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-82",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 110.800000071525574, 164.400001108646393, 113.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 112.400000095367432, 142.000000774860382, 113.0, 20.0 ],
									"style" : "default",
									"text" : "delay-line scrubber"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-83",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 110.800000071525574, 137.200001001358032, 191.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 112.400000095367432, 114.800000667572021, 191.0, 20.0 ],
									"style" : "default",
									"text" : "stereo granulator and pitch-shifter"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-84",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 110.800000071525574, 82.800000786781311, 97.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 112.400000095367432, 60.4000004529953, 97.0, 20.0 ],
									"style" : "default",
									"text" : "dc-bias remover"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.203921568627451, 0.435294117647059, 0.270588235294118, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-85",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.399999856948853, 163.920001012086857, 45.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 20.99999988079071, 141.520000678300846, 45.0, 22.0 ],
									"style" : "default",
									"text" : "scrub~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.203921568627451, 0.435294117647059, 0.270588235294118, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-86",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.399999856948853, 136.880000936985027, 56.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 20.99999988079071, 114.480000603199016, 56.0, 22.0 ],
									"style" : "default",
									"text" : "munger~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.203921568627451, 0.435294117647059, 0.270588235294118, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-87",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 19.399999856948853, 82.800000786781311, 56.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 20.99999988079071, 60.4000004529953, 56.0, 22.0 ],
									"style" : "default",
									"text" : "dcblock~"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-10", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-12", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-14", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-16", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-18", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-198", 0 ],
									"hidden" : 1,
									"source" : [ "obj-199", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-2", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-20", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-199", 0 ],
									"hidden" : 1,
									"source" : [ "obj-200", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-22", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-24", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-26", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-50", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-52", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-54", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-57", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-6", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-8", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-81", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-85", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-86", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-87", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 630.050002098083496, 131.923340439796448, 96.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p \"random DSP\""
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-108",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 8,
							"minor" : 1,
							"revision" : 8,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ -2113.0, 47.0, 689.0, 353.0 ],
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
						"showontab" : 1,
						"assistshowspatchername" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-198",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 38.0, 646.4000044465065, 64.0, 24.0 ],
									"text" : "pcontrol"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-199",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 38.0, 613.4000044465065, 59.0, 24.0 ],
									"text" : "help $1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-200",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 38.0, 582.4000044465065, 116.0, 24.0 ],
									"text" : "prepend symbol"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-50",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 2.999999821186066, 36.600000321865082, 150.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 3.800000011920929, 37.400000333786011, 150.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontface" : 1,
									"fontsize" : 18.0,
									"id" : "obj-48",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 2.999999821186066, 4.599999845027924, 226.0, 27.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 3.800000011920929, 5.399999856948853, 226.0, 27.0 ],
									"text" : "Physical Models"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-3",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 118.200000000000003, 529.000002264976274, 239.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 387.00000411272049, 286.994172304857329, 121.0, 20.0 ],
									"style" : "default",
									"text" : "a really insulting sitar"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgcolor2" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.129411764705882, 0.674509803921569, 0.462745098039216, 1.0 ],
									"bgfillcolor_color1" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-4",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 529.000002264976274, 47.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 305.600003957748413, 285.994172304857329, 38.0, 22.0 ],
									"style" : "default",
									"text" : "sitar~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-31",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 118.200000000000003, 494.917649190566067, 239.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 387.00000411272049, 258.819900747378654, 116.0, 20.0 ],
									"style" : "default",
									"text" : "a cute police whistle"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgcolor2" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.129411764705882, 0.674509803921569, 0.462745098039216, 1.0 ],
									"bgfillcolor_color1" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-32",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 501.635296243078301, 63.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 305.600003957748413, 257.694900747378654, 52.0, 22.0 ],
									"style" : "default",
									"text" : "whistle~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-33",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 118.200000000000003, 468.035296116155678, 236.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 387.00000411272049, 230.645629189899978, 76.0, 20.0 ],
									"style" : "default",
									"text" : "a stiffy string"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgcolor2" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.129411764705882, 0.674509803921569, 0.462745098039216, 1.0 ],
									"bgfillcolor_color1" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-34",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 474.270590221180385, 74.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 305.600003957748413, 229.395629189899978, 61.0, 22.0 ],
									"style" : "default",
									"text" : "stif_karp~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-35",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 118.200000000000003, 441.152943041745289, 239.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 387.00000411272049, 202.471357632421302, 137.0, 20.0 ],
									"style" : "default",
									"text" : "this one is real simple...."
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgcolor2" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.129411764705882, 0.674509803921569, 0.462745098039216, 1.0 ],
									"bgfillcolor_color1" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-36",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 446.905884199282468, 57.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 305.600003957748413, 201.096357632421302, 50.0, 22.0 ],
									"style" : "default",
									"text" : "simple~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-37",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 118.200000000000003, 414.270589967334899, 237.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 387.00000411272049, 174.297086074942627, 93.0, 20.0 ],
									"style" : "default",
									"text" : "fony saxophone"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgcolor2" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.129411764705882, 0.674509803921569, 0.462745098039216, 1.0 ],
									"bgfillcolor_color1" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-38",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 419.541178177384552, 73.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 305.600003957748413, 172.797086074942627, 64.0, 22.0 ],
									"style" : "default",
									"text" : "saxofony~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-39",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 118.200000000000003, 387.38823689292451, 240.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 387.00000411272049, 146.122814517463951, 135.0, 20.0 ],
									"style" : "default",
									"text" : "waveguide mesh model"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgcolor2" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.129411764705882, 0.674509803921569, 0.462745098039216, 1.0 ],
									"bgfillcolor_color1" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-40",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 392.176472155486636, 66.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 305.600003957748413, 144.497814517463951, 60.0, 22.0 ],
									"style" : "default",
									"text" : "mesh2D~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-41",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 118.200000000000003, 360.505883818514121, 238.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 387.00000411272049, 117.948542959985275, 105.0, 20.0 ],
									"style" : "default",
									"text" : "fancy clarinet stuff"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgcolor2" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.129411764705882, 0.674509803921569, 0.462745098039216, 1.0 ],
									"bgfillcolor_color1" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-42",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 364.811766133588719, 80.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 305.600003957748413, 116.198542959985275, 70.0, 22.0 ],
									"style" : "default",
									"text" : "blow_hole~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-43",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 118.200000000000003, 333.623530744103732, 235.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 387.00000411272049, 89.774271402506599, 73.0, 20.0 ],
									"style" : "default",
									"text" : "blown bottle"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgcolor2" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.129411764705882, 0.674509803921569, 0.462745098039216, 1.0 ],
									"bgfillcolor_color1" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-44",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 337.447060111690803, 77.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 305.600003957748413, 87.899271402506599, 66.0, 22.0 ],
									"style" : "default",
									"text" : "blow_botl~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-45",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 118.200000000000003, 306.741177669693343, 240.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 387.00000411272049, 61.599999845027924, 145.0, 20.0 ],
									"style" : "default",
									"text" : "banded waveguide model"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgcolor2" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.129411764705882, 0.674509803921569, 0.462745098039216, 1.0 ],
									"bgfillcolor_color1" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-46",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 310.082354089792886, 78.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 305.600003957748413, 59.599999845027924, 76.0, 22.0 ],
									"style" : "default",
									"text" : "bandedWG~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-58",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 118.200000000000003, 279.858824595282954, 239.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 91.800000190734863, 286.994172304857329, 146.0, 20.0 ],
									"style" : "default",
									"text" : "monster blotar~ gone wild"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgcolor2" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.129411764705882, 0.674509803921569, 0.462745098039216, 1.0 ],
									"bgfillcolor_color1" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-59",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 282.71764806789497, 58.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 15.800000190734863, 285.994172304857329, 58.0, 22.0 ],
									"style" : "default",
									"text" : "ublotar~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-150",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 118.200000000000003, 252.976471520872565, 238.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 91.800000190734863, 258.569900747378654, 122.0, 20.0 ],
									"style" : "default",
									"text" : "plucked string model"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-151",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 118.200000000000003, 226.094118446462204, 238.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 91.800000190734863, 230.145629189899978, 143.0, 20.0 ],
									"style" : "default",
									"text" : "mandolin physical model"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-152",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 118.200000000000003, 199.211765372051843, 238.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 91.800000190734863, 201.721357632421302, 117.0, 20.0 ],
									"style" : "default",
									"text" : "flute physical model"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-153",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 118.200000000000003, 172.329412297641483, 239.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 91.800000190734863, 173.297086074942627, 133.0, 20.0 ],
									"style" : "default",
									"text" : "clarinet physical model"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-154",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 118.200000000000003, 145.447059223231122, 240.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 91.800000190734863, 144.872814517463951, 160.0, 20.0 ],
									"style" : "default",
									"text" : "model for brass instruments"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-155",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 118.200000000000003, 118.564706148820747, 239.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 91.800000190734863, 116.448542959985275, 175.0, 20.0 ],
									"style" : "default",
									"text" : "bowed string resonance model"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-156",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 118.200000000000003, 91.682353074410372, 241.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 91.800000190734863, 88.024271402506599, 188.0, 20.0 ],
									"style" : "default",
									"text" : "model of a bowed percussion bar"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-157",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 118.200000000000003, 64.799999999999997, 239.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 91.800000190734863, 59.599999845027924, 129.0, 20.0 ],
									"style" : "default",
									"text" : "evil mutant flute-guitar"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgcolor2" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.129411764705882, 0.674509803921569, 0.462745098039216, 1.0 ],
									"bgfillcolor_color1" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-178",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 255.352942045997054, 57.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 15.800000190734863, 257.694900747378654, 57.0, 22.0 ],
									"style" : "default",
									"text" : "plucked~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgcolor2" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.129411764705882, 0.674509803921569, 0.462745098039216, 1.0 ],
									"bgfillcolor_color1" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-179",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 227.988236024099137, 68.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 15.800000190734863, 229.395629189899978, 68.0, 22.0 ],
									"style" : "default",
									"text" : "mandolin~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgcolor2" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.129411764705882, 0.674509803921569, 0.462745098039216, 1.0 ],
									"bgfillcolor_color1" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-180",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 200.623530002201221, 43.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 15.800000190734863, 201.096357632421302, 43.0, 22.0 ],
									"style" : "default",
									"text" : "flute~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgcolor2" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.129411764705882, 0.674509803921569, 0.462745098039216, 1.0 ],
									"bgfillcolor_color1" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-181",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 173.258823980303305, 40.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 15.800000190734863, 172.797086074942627, 40.0, 22.0 ],
									"style" : "default",
									"text" : "clar~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgcolor2" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.129411764705882, 0.674509803921569, 0.462745098039216, 1.0 ],
									"bgfillcolor_color1" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-182",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 145.894117958405388, 49.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 15.800000190734863, 144.497814517463951, 49.0, 22.0 ],
									"style" : "default",
									"text" : "brass~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgcolor2" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.129411764705882, 0.674509803921569, 0.462745098039216, 1.0 ],
									"bgfillcolor_color1" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-183",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 118.529411936507472, 54.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 15.800000190734863, 116.198542959985275, 54.0, 22.0 ],
									"style" : "default",
									"text" : "bowed~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgcolor2" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.129411764705882, 0.674509803921569, 0.462745098039216, 1.0 ],
									"bgfillcolor_color1" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-184",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 91.164705914609556, 71.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 15.800000190734863, 87.899271402506599, 71.0, 22.0 ],
									"style" : "default",
									"text" : "bowedbar~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgcolor2" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.129411764705882, 0.674509803921569, 0.462745098039216, 1.0 ],
									"bgfillcolor_color1" : [ 0.156862745098039, 0.8, 0.549019607843137, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-197",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 63.799999892711639, 53.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 15.800000190734863, 59.599999845027924, 53.0, 22.0 ],
									"style" : "default",
									"text" : "blotar~"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-178", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-179", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-180", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-181", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"hidden" : 1,
									"source" : [ "obj-182", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-183", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-184", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-197", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-198", 0 ],
									"hidden" : 1,
									"source" : [ "obj-199", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-199", 0 ],
									"hidden" : 1,
									"source" : [ "obj-200", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-32", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-34", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-36", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-38", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-40", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-42", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-44", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-46", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"source" : [ "obj-59", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 613.703847706317902, 73.800252437591553, 112.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p \"physical models\""
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-71",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 8,
							"minor" : 1,
							"revision" : 8,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ 0.0, 26.0, 689.0, 353.0 ],
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
						"showontab" : 1,
						"assistshowspatchername" : 0,
						"title" : "PhiSM/PHoLIES",
						"boxes" : [ 							{
								"box" : 								{
									"id" : "obj-50",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 4.800000071525574, 37.600000560283661, 150.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 4.800000071525574, 37.600000560283661, 150.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontface" : 1,
									"fontsize" : 18.0,
									"id" : "obj-48",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 4.800000071525574, 5.600000083446503, 226.0, 27.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 4.800000071525574, 5.600000083446503, 226.0, 27.0 ],
									"text" : "PhiSM/PHoLIES"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-46",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 381.333341121673584, 200.511116690105837, 181.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 378.333341538906097, 159.711114651626986, 181.0, 20.0 ],
									"text" : "Perry Cook's PhiSM instruments"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-44",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 381.333341121673584, 233.733339905738831, 150.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 378.333341538906097, 192.933337867259979, 150.0, 20.0 ],
									"text" : "all of the models"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-42",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 381.333341121673584, 167.288893474472843, 150.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 378.333341538906097, 126.488891435993992, 150.0, 20.0 ],
									"text" : "water droplet model"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-40",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 381.333341121673584, 134.066670258839906, 150.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 378.333341538906097, 93.266668220361055, 150.0, 20.0 ],
									"text" : "tambourine model"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-38",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 381.333341121673584, 100.844447043206969, 101.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 378.333341538906097, 60.044445004728118, 101.0, 20.0 ],
									"text" : "sleighbells model"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-36",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 105.333337008953094, 235.288895461294373, 124.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 86.333337187767029, 194.488893422815522, 124.0, 20.0 ],
									"text" : "maraca shaker model"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-34",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 105.333337008953094, 202.066672245661408, 81.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 86.333337187767029, 161.266670207182557, 81.0, 20.0 ],
									"text" : "sekere model"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-30",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 105.333337008953094, 168.844449030028443, 71.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 86.333337187767029, 128.044446991549592, 71.0, 20.0 ],
									"text" : "guiro model"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-28",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 105.333337008953094, 135.622225814395478, 123.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 86.333337187767029, 94.822223775916626, 123.0, 20.0 ],
									"text" : "cabasa shaker model"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-26",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 105.333337008953094, 102.400002598762512, 151.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 86.333337187767029, 61.600000560283661, 151.0, 20.0 ],
									"text" : "bamboo wind chime model"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.847058823529412, 0.517647058823529, 0.517647058823529, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-24",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 291.00000387430191, 232.733339905738831, 58.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 288.000004291534424, 191.933337867259979, 58.0, 22.0 ],
									"text" : "shakers~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.847058823529412, 0.517647058823529, 0.517647058823529, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-22",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 291.00000387430191, 199.400005578994751, 78.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 288.000004291534424, 158.6000035405159, 78.0, 22.0 ],
									"text" : "metashaker~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.847058823529412, 0.517647058823529, 0.517647058823529, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-20",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 291.00000387430191, 166.066671252250671, 45.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 288.000004291534424, 125.26666921377182, 45.0, 22.0 ],
									"text" : "wuter~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.847058823529412, 0.517647058823529, 0.517647058823529, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-18",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 291.00000387430191, 132.733336925506592, 42.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 288.000004291534424, 91.93333488702774, 42.0, 22.0 ],
									"text" : "tamb~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.847058823529412, 0.517647058823529, 0.517647058823529, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-16",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 291.00000387430191, 99.400002598762512, 47.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 288.000004291534424, 58.600000560283661, 47.0, 22.0 ],
									"text" : "sleigh~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.847058823529412, 0.517647058823529, 0.517647058823529, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-14",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 14.999999761581421, 233.733339905738831, 52.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 12.000000178813934, 192.933337867259979, 52.0, 22.0 ],
									"text" : "shaker~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.847058823529412, 0.517647058823529, 0.517647058823529, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-12",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 14.999999761581421, 200.400005578994751, 52.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 12.000000178813934, 159.6000035405159, 52.0, 22.0 ],
									"text" : "sekere~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.847058823529412, 0.517647058823529, 0.517647058823529, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-10",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 14.999999761581421, 167.066671252250671, 42.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 12.000000178813934, 126.26666921377182, 42.0, 22.0 ],
									"text" : "guiro~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.847058823529412, 0.517647058823529, 0.517647058823529, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-8",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 14.999999761581421, 133.733336925506592, 54.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 12.000000178813934, 92.93333488702774, 54.0, 22.0 ],
									"text" : "cabasa~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.847058823529412, 0.517647058823529, 0.517647058823529, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-6",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 14.999999761581421, 100.400002598762512, 59.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 12.000000178813934, 59.600000560283661, 59.0, 22.0 ],
									"text" : "bamboo~"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-198",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 14.999999761581421, 389.200001060962677, 64.0, 24.0 ],
									"text" : "pcontrol"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-199",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 14.999999761581421, 356.200001060962677, 59.0, 24.0 ],
									"text" : "help $1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-200",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 14.999999761581421, 325.200001060962677, 116.0, 24.0 ],
									"text" : "prepend symbol"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"hidden" : 1,
									"source" : [ "obj-10", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"hidden" : 1,
									"source" : [ "obj-12", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"hidden" : 1,
									"source" : [ "obj-14", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"hidden" : 1,
									"source" : [ "obj-16", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"hidden" : 1,
									"source" : [ "obj-18", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-198", 0 ],
									"hidden" : 1,
									"source" : [ "obj-199", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"hidden" : 1,
									"source" : [ "obj-20", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-199", 0 ],
									"hidden" : 1,
									"source" : [ "obj-200", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"hidden" : 1,
									"source" : [ "obj-22", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"hidden" : 1,
									"source" : [ "obj-24", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"hidden" : 1,
									"source" : [ "obj-6", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"hidden" : 1,
									"source" : [ "obj-8", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 605.203818917274475, 44.738708436489105, 107.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p PhiSM/PHoLIES"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-70",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 8,
							"minor" : 1,
							"revision" : 8,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ 0.0, 26.0, 689.0, 353.0 ],
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
						"showontab" : 1,
						"assistshowspatchername" : 0,
						"title" : "modal/formant",
						"boxes" : [ 							{
								"box" : 								{
									"id" : "obj-14",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 107.800000071525574, 158.400002360343933, 150.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 103.400000035762787, 128.40000194311142, 150.0, 20.0 ],
									"text" : "vibraphone model"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-12",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 107.800000071525574, 123.200001835823059, 150.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 103.400000035762787, 93.900001138448715, 150.0, 20.0 ],
									"text" : "struck marimba model"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-10",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 107.800000071525574, 89.400000751018524, 150.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 103.400000035762787, 59.400000333786011, 150.0, 20.0 ],
									"text" : "agogo model"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-50",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 6.199999868869781, 37.400000333786011, 150.0, 20.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 6.199999868869781, 37.400000333786011, 150.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontface" : 1,
									"fontsize" : 18.0,
									"id" : "obj-48",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 6.199999868869781, 5.399999856948853, 238.0, 27.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 6.199999868869781, 5.399999856948853, 238.0, 27.0 ],
									"text" : "Modal / Formant Synthesis"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.674509803921569, 0.517647058823529, 0.32156862745098, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-8",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 17.0, 123.200001835823059, 62.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 12.599999964237213, 93.900001138448715, 62.0, 22.0 ],
									"text" : "marimba~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.674509803921569, 0.517647058823529, 0.32156862745098, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-6",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 17.0, 158.400002360343933, 75.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 12.599999964237213, 128.40000194311142, 75.0, 22.0 ],
									"text" : "vibraphone~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgcolor2" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_angle" : 270.0,
									"bgfillcolor_autogradient" : 0.0,
									"bgfillcolor_color" : [ 0.674509803921569, 0.517647058823529, 0.32156862745098, 1.0 ],
									"bgfillcolor_color1" : [ 0.301961, 0.301961, 0.301961, 1.0 ],
									"bgfillcolor_color2" : [ 0.2, 0.2, 0.2, 1.0 ],
									"bgfillcolor_proportion" : 0.5,
									"bgfillcolor_type" : "color",
									"gradient" : 1,
									"id" : "obj-4",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 17.0, 89.400000751018524, 49.0, 22.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 12.599999964237213, 59.400000333786011, 49.0, 22.0 ],
									"text" : "agogo~"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-198",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 17.0, 316.0, 64.0, 24.0 ],
									"text" : "pcontrol"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-199",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 17.0, 283.0, 59.0, 24.0 ],
									"text" : "help $1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"hidden" : 1,
									"id" : "obj-200",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 17.0, 252.0, 116.0, 24.0 ],
									"text" : "prepend symbol"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-198", 0 ],
									"hidden" : 1,
									"source" : [ "obj-199", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-199", 0 ],
									"hidden" : 1,
									"source" : [ "obj-200", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"hidden" : 1,
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"hidden" : 1,
									"source" : [ "obj-6", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-200", 0 ],
									"hidden" : 1,
									"source" : [ "obj-8", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 595.742293357849121, 15.677164435386658, 95.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p modal/formant"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-55",
					"maxclass" : "fpic",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "jit_matrix" ],
					"patching_rect" : [ 6.0, 5.876911997795105, 137.0, 80.123088002204895 ],
					"pic" : "percolate.jpg",
					"presentation" : 1,
					"presentation_rect" : [ 6.0, 6.664313614368439, 137.0, 80.123088002204895 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.0,
					"hidden" : 1,
					"id" : "obj-66",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 538.118107855319977, 15.677164435386658, 44.0, 19.0 ],
					"text" : "onecopy"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.0,
					"hidden" : 1,
					"id" : "obj-93",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 8,
							"minor" : 1,
							"revision" : 8,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ 50.0, 40.0, 405.0, 234.0 ],
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
						"assistshowspatchername" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"id" : "obj-1",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 19.0, 34.0, 157.0, 22.0 ],
									"text" : "Real-Time Cmix:"
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"hidden" : 1,
									"id" : "obj-2",
									"index" : 1,
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 5.0, 400.0, 15.0, 15.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 9.0,
									"id" : "obj-3",
									"linecount" : 6,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 19.0, 57.0, 356.0, 67.0 ],
									"text" : "RTcmix is a complete open-source synthesis and signal-processing package based on Paul Lansky's CMIX software, which was developed at Princeton University in the 1980's. It runs on Linux and Irix, and is maintained by Brad Garton (at Columbia University) and Dave Topper (at the University of Virginia). It allows for real-time score processing, event streaming over TCP/IP, and has examples for interfacing parsers in C/C++ and Lisp, as well as interfaces in X/Motif."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 9.0,
									"id" : "obj-4",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 19.0, 145.0, 273.0, 17.0 ],
									"text" : "for more information: http://www.music.columbia.edu/cmix"
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"hidden" : 1,
									"id" : "obj-5",
									"index" : 2,
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 6.0, 2.0, 15.0, 15.0 ]
								}

							}
 ],
						"lines" : [  ]
					}
,
					"patching_rect" : [ 277.118113160133362, 210.694369614124298, 45.0, 19.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p rtcmix"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.0,
					"hidden" : 1,
					"id" : "obj-94",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 277.118113160133362, 160.607755064964294, 40.59842586517334, 19.0 ],
					"text" : "open"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.0,
					"hidden" : 1,
					"id" : "obj-95",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 277.118113160133362, 186.544763147830963, 45.0, 19.0 ],
					"text" : "pcontrol"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.0,
					"hidden" : 1,
					"id" : "obj-96",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "bang" ],
					"patching_rect" : [ 277.118113160133362, 138.607755064964294, 27.0, 19.0 ],
					"text" : "b"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.0,
					"id" : "obj-97",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 277.118113160133362, 117.607755064964294, 112.0, 19.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 219.688975751399994, 94.6983442902565, 97.0, 19.0 ],
					"text" : "about real-time cmix..."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.0,
					"hidden" : 1,
					"id" : "obj-98",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 8,
							"minor" : 1,
							"revision" : 8,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ 137.0, 207.0, 400.0, 300.0 ],
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
						"assistshowspatchername" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"id" : "obj-1",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 20.0, 27.0, 157.0, 22.0 ],
									"text" : "the synthesis toolkit:"
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"hidden" : 1,
									"id" : "obj-2",
									"index" : 1,
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 6.0, 393.0, 15.0, 15.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 9.0,
									"id" : "obj-3",
									"linecount" : 11,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 20.0, 50.0, 358.0, 117.0 ],
									"text" : "STK is a set of audio signal processing C++ classes and instruments for music synthesis. You can use these classes to create programs which make cool sounds using a variety of synthesis techniques. This is not a terribly novel concept, except that STK is very portable (it's mostly platform-independent C and C++ code) AND it's completely user-extensible. So, the code you write using STK actually has some chance of working in another 5-10 years. STK currently runs on SGI (Irix), Linux, NeXTStep, and Windows computer platforms. Oh, and it's free for non-commercial use. The only parts of STK that are platform-dependent concern real-time sound and MIDI input and output ... but we've taken care of that for you. The interface for MIDI input and the simple Tcl/Tk graphical user interfaces (GUIs) provided is the same, so it's easy to voice and experiment in real time using either the GUIs or MIDI."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 9.0,
									"id" : "obj-4",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 20.0, 211.0, 273.0, 27.0 ],
									"text" : "for more information: http://www-ccrma.stanford.edu/CCRMA/Software/STK/"
								}

							}
 ],
						"lines" : [  ]
					}
,
					"patching_rect" : [ 155.236221015453339, 207.544763147830963, 30.0, 19.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p stk"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.0,
					"hidden" : 1,
					"id" : "obj-99",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 155.236221015453339, 162.607755064964294, 49.259843647480011, 19.0 ],
					"text" : "open"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.0,
					"hidden" : 1,
					"id" : "obj-100",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 155.236221015453339, 186.544763147830963, 45.0, 19.0 ],
					"text" : "pcontrol"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.0,
					"hidden" : 1,
					"id" : "obj-101",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "bang" ],
					"patching_rect" : [ 155.236221015453339, 140.607755064964294, 27.0, 19.0 ],
					"text" : "b"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.0,
					"id" : "obj-102",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 155.236221015453339, 117.607755064964294, 75.0, 19.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 124.0, 94.6983442902565, 68.0, 19.0 ],
					"text" : "about the stk..."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.0,
					"hidden" : 1,
					"id" : "obj-103",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 8,
							"minor" : 1,
							"revision" : 8,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ 136.0, 222.0, 559.0, 509.0 ],
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
						"assistshowspatchername" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 9.0,
									"id" : "obj-1",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 60.0, 349.0, 160.0, 17.0 ],
									"text" : "http://music.columbia.edu/~luke"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 14.0,
									"id" : "obj-2",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 13.0, 20.0, 108.0, 22.0 ],
									"text" : "dan and luke..."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 9.0,
									"id" : "obj-3",
									"linecount" : 10,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 13.0, 212.0, 360.0, 107.0 ],
									"text" : "• r. luke dubois (luke@music.columbia.edu) is a composer, programmer, and video artist living in new york city. he recently completed his doctorate in music composition at columbia university, where he studied with fred lerdahl and jonathan kramer. he teaches graduate and undergraduate electronic music and new media courses at the columbia university computer music center (cmc), and at the school of education and tisch school of the arts at new york university. he has done interactive programming and music production work for many artists, most recently toni dove, chris mann, elliott sharp, and michael gordon, and was a staff programming consultant for Engine27 for the 2003 season. his music with his band, the freight elevator quartet, is available on caipirinha/sire and cycling'74 music."
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"hidden" : 1,
									"id" : "obj-4",
									"index" : 1,
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 6.0, 2.0, 15.0, 15.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 9.0,
									"id" : "obj-5",
									"linecount" : 8,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 13.0, 43.0, 355.0, 87.0 ],
									"text" : "• dan trueman (dan@music.princeton.edu) composes and plays both the 6-string electric violin and the norwegian hardanger fiddle. His duo \"trollstilt\" (with guitarist monica mugan) recently completed a compact disc of original tunes inspired by his activities as a traditional hardanger fiddler. he has been active as an experimental instrument designer, and has built sensor bows, spherical speakers, and, most recently, the Bowed-Sensor-Speaker-Array. dans electronic improvisation ensemble \"interface\" (with curtis bahn) recently released its first CD--./swank--with C74Records. he teaches at princeton university. visit his websites for more information:"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 9.0,
									"id" : "obj-6",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 60.0, 159.0, 208.0, 17.0 ],
									"text" : "http://music.princeton.edu/~dan"
								}

							}
 ],
						"lines" : [  ]
					}
,
					"patching_rect" : [ 27.0, 203.532991170883179, 50.0, 19.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p authors"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.0,
					"hidden" : 1,
					"id" : "obj-104",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 27.0, 162.532991170883179, 50.0, 19.0 ],
					"text" : "open"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.0,
					"hidden" : 1,
					"id" : "obj-105",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 27.0, 182.532991170883179, 45.0, 19.0 ],
					"text" : "pcontrol"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.0,
					"hidden" : 1,
					"id" : "obj-106",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "bang" ],
					"patching_rect" : [ 27.0, 140.532991170883179, 27.0, 19.0 ],
					"text" : "b"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.0,
					"id" : "obj-107",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 27.0, 117.532991170883179, 95.0, 19.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 6.0, 94.6983442902565, 86.0, 19.0 ],
					"text" : "about the authors..."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.0,
					"id" : "obj-196",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 145.0, 1.0, 168.0, 37.0 ],
					"presentation" : 1,
					"presentation_linecount" : 3,
					"presentation_rect" : [ 148.688975751399994, 6.664313614368439, 168.0, 37.0 ],
					"text" : "• by dan trueman and r. luke dubois, computer music center, columbia university in the city of new york."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 9.0,
					"id" : "obj-203",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 238.0, 45.0, 265.0, 27.0 ],
					"presentation" : 1,
					"presentation_linecount" : 3,
					"presentation_rect" : [ 148.688975751399994, 49.787401616573334, 168.0, 37.0 ],
					"text" : "big ups to perry cook and gary scavone for the synthesis toolkit, and brad garton and dave topper for rtcmix."
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-98", 0 ],
					"hidden" : 1,
					"source" : [ "obj-100", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-99", 0 ],
					"hidden" : 1,
					"source" : [ "obj-101", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-101", 0 ],
					"hidden" : 1,
					"source" : [ "obj-102", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-105", 0 ],
					"hidden" : 1,
					"source" : [ "obj-104", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-103", 0 ],
					"hidden" : 1,
					"source" : [ "obj-105", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-104", 0 ],
					"hidden" : 1,
					"source" : [ "obj-106", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-106", 0 ],
					"hidden" : 1,
					"source" : [ "obj-107", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-95", 0 ],
					"hidden" : 1,
					"source" : [ "obj-94", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-93", 1 ],
					"hidden" : 1,
					"source" : [ "obj-95", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-94", 0 ],
					"hidden" : 1,
					"source" : [ "obj-96", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-96", 0 ],
					"hidden" : 1,
					"source" : [ "obj-97", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-100", 0 ],
					"hidden" : 1,
					"source" : [ "obj-99", 0 ]
				}

			}
 ],
		"dependency_cache" : [ 			{
				"name" : "percolate.jpg",
				"bootpath" : "~/Documents/Max Third Party Externals/dev/percolate/media",
				"patcherrelativepath" : "../../../../Max Third Party Externals/dev/percolate/media",
				"type" : "JPEG",
				"implicit" : 1
			}
 ],
		"autosave" : 0
	}

}
