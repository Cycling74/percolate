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
		"rect" : [ 52.0, 93.0, 402.0, 379.0 ],
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
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 103.5, 403.0, 274.0, 21.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 78.5, 323.444444444444514, 274.0, 21.0 ],
					"text" : "Hanning and Hamming window function generator"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-12",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 103.5, 363.571428571428555, 274.0, 21.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 78.5, 294.238095238095298, 274.0, 21.0 ],
					"text" : "Breakpoint function generator"
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
					"patching_rect" : [ 103.5, 324.14285714285711, 274.0, 21.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 78.5, 265.031746031746025, 274.0, 21.0 ],
					"text" : "Random function generator"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-10",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 103.5, 284.714285714285666, 274.0, 21.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 78.5, 235.825396825396865, 274.0, 21.0 ],
					"text" : "Chebyshev polynomial solver"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-9",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 103.5, 245.285714285714249, 274.0, 21.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 78.5, 206.61904761904762, 274.0, 21.0 ],
					"text" : "Harmonic bandpass filtered wavetable generator"
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
					"patching_rect" : [ 103.5, 205.857142857142833, 274.0, 21.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 78.5, 177.412698412698404, 274.0, 21.0 ],
					"text" : "Sinusoidal bandpass filtered wavetable generator"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-7",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 103.5, 166.428571428571416, 274.0, 21.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 78.5, 148.206349206349188, 274.0, 21.0 ],
					"text" : "Linear bandpass filtered wavetable generator"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-18",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 103.5, 127.0, 274.0, 21.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 78.5, 119.0, 274.0, 21.0 ],
					"text" : "Exponential bandpass filtered wavetable generator"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-63",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 52.0, 205.857142857142833, 44.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 23.0, 177.202722647976231, 44.0, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "gen9"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-64",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 52.0, 166.428571428571416, 44.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 23.0, 148.101361323988129, 44.0, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "gen7"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-65",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 52.0, 127.0, 44.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 23.0, 119.0, 44.0, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "gen5"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-90",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 52.0, 403.0, 44.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 23.0, 322.709529267916878, 44.0, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "gen25"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-173",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 52.0, 363.571428571428555, 44.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 23.0, 293.60816794392872, 44.0, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "gen24"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-174",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 52.0, 324.14285714285711, 44.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 23.0, 264.506806619940676, 44.0, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "gen20"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-175",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 52.0, 284.714285714285666, 44.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 23.0, 235.405445295952518, 44.0, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "gen17"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-176",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 52.0, 245.285714285714249, 44.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 23.0, 206.30408397196436, 44.0, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "gen10"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-6",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 52.0, 527.0, 51.0, 22.0 ],
					"text" : "pcontrol"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-5",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 52.0, 497.0, 48.0, 22.0 ],
					"text" : "help $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-2",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 52.0, 466.0, 94.0, 22.0 ],
					"text" : "prepend symbol"
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
					"patching_rect" : [ 7.5, 67.0, 108.0, 30.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 7.5, 67.0, 108.0, 30.0 ],
					"text" : "Generators"
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
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-173", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-174", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-175", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-176", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-5", 0 ],
					"source" : [ "obj-2", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-63", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-64", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-65", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"source" : [ "obj-90", 0 ]
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
