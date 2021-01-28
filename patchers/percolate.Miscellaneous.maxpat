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
		"rect" : [ 717.0, 216.0, 327.0, 370.0 ],
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
					"id" : "obj-11",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 142.0, 328.584616746352197, 101.0, 35.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 113.600003957748413, 154.560000753402733, 170.0, 21.0 ],
					"text" : "2D rectilinear waveguide mesh"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-8",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 191.0, 292.584616746352197, 101.0, 35.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 113.600003957748413, 276.387693366087319, 132.0, 21.0 ],
					"text" : "2D wavetable oscillator"
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
					"patching_rect" : [ 90.600003957748413, 241.976082021288789, 101.0, 35.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 113.600003957748413, 316.584616746352197, 174.0, 21.0 ],
					"text" : "Voice formant synthesis"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-3",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 82.600003957748413, 205.471357632421302, 101.0, 35.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 113.600003957748413, 197.976082021288789, 174.0, 21.0 ],
					"text" : "Perry R. Cook's FM instruments"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-1",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 154.5, 202.599999845027924, 101.0, 35.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 113.600003957748413, 236.19076998582247, 158.0, 21.0 ],
					"text" : "Noise/wavetable instrument"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-10",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 200.5, 378.916669905185699, 100.0, 50.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 113.600003957748413, 115.599999845027924, 143.0, 21.0 ],
					"text" : "Banded waveguide model"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-5",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 15.100004470348381, 472.0, 51.0, 22.0 ],
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
					"patching_rect" : [ 15.100004470348381, 442.0, 48.0, 22.0 ],
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
					"patching_rect" : [ 15.100004470348381, 411.0, 94.0, 22.0 ],
					"text" : "prepend symbol"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-36",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 9.999999999999986, 346.905884199282468, 58.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 23.600003957748413, 236.19076998582247, 76.0, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "simple~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-46",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 10.0, 303.082354089792886, 79.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 23.600003957748413, 115.599999845027924, 76.0, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "bandedWG~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-14",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 7.600004470348381, 259.960001087188743, 60.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 23.600003957748413, 155.796923225292772, 76.0, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "mesh2D~"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Futura",
					"fontsize" : 18.0,
					"id" : "obj-2",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 7.5, 67.0, 124.0, 30.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 7.5, 66.276924016842429, 124.0, 30.0 ],
					"text" : "Miscellaneous"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-28",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 7.600004470348381, 219.584616805956841, 88.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 23.600003957748413, 316.584616746352197, 76.0, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "voice_form~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-30",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 7.600004470348381, 178.507693623579428, 64.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 23.600003957748413, 195.993846605557621, 75.800000488758087, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "prc_fm~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-77",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 7.600004470348381, 141.276924076447074, 60.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 23.600003957748413, 276.387693366087319, 76.0, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "terrain~"
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
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-28", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-30", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-36", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-46", 0 ]
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
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-77", 0 ]
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
