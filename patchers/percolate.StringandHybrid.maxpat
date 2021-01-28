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
		"rect" : [ 370.0, 326.0, 324.0, 428.0 ],
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
					"id" : "obj-17",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 98.800000190734863, 303.395629189899978, 100.0, 35.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 113.5, 121.694900747378654, 143.0, 21.0 ],
					"text" : "Plucked string model"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-16",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 314.5, 160.198542959985275, 100.0, 50.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 113.5, 266.212100231749673, 173.0, 21.0 ],
					"text" : "Bowed percussion bar model"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-15",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 390.800000190734863, 279.395629189899978, 100.0, 21.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 113.5, 230.082800360656904, 143.0, 21.0 ],
					"text" : "Sitar model"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-14",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 88.5, 199.395629189899978, 100.0, 35.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 113.5, 302.198542959985275, 173.0, 21.0 ],
					"text" : "Bowed string resonance model"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-13",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 84.800000190734863, 224.395629189899978, 100.0, 21.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 113.5, 193.953500489564135, 143.0, 21.0 ],
					"text" : "Mandolin model"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-11",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 90.800000190734863, 330.395629189899978, 100.0, 35.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 113.5, 374.59999984502798, 115.0, 21.0 ],
					"text" : "Mutant flute-guitar"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-6",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 121.00000411272049, 385.40000194311142, 100.0, 50.0 ],
					"presentation" : 1,
					"presentation_linecount" : 2,
					"presentation_rect" : [ 113.5, 151.324200618471423, 143.0, 35.0 ],
					"text" : "Modified Karplus-Strong string synthesis"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-5",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 14.5, 515.0, 51.0, 22.0 ],
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
					"patching_rect" : [ 14.5, 485.0, 48.0, 22.0 ],
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
					"patching_rect" : [ 14.5, 454.0, 94.0, 22.0 ],
					"text" : "prepend symbol"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-10",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 277.5, 83.916669905185728, 100.0, 35.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 113.5, 338.470699973935211, 115.0, 21.0 ],
					"text" : "Hybrid flute-guitar"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-2",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 13.0, 179.0, 48.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 20.800000190734863, 230.082800360656904, 74.0, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "sitar~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-183",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 13.0, 395.529411936507472, 55.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 20.800000190734863, 302.341400102842442, 74.19999623298645, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "bowed~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-184",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 13.0, 368.164705914609556, 72.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 20.800000190734863, 266.212100231749673, 74.0, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "bowedbar~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-197",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 13.0, 340.799999892711639, 54.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 20.800000190734863, 338.470699973935211, 74.19999623298645, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "blotar~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-59",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 13.0, 297.71764806789497, 59.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 20.100000381469727, 374.59999984502798, 74.699999809265137, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "ublotar~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-178",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 13.0, 270.352942045997054, 57.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 20.800000190734863, 121.694900747378654, 73.699999809265137, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "plucked~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-179",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 13.0, 242.988236024099137, 69.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 20.800000190734863, 193.953500489564135, 74.0, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "mandolin~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-34",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 13.0, 134.270590221180385, 75.0, 22.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 20.800000190734863, 157.824200618471394, 73.699999809265137, 22.0 ],
					"style" : "Max 12 Regular",
					"text" : "stif_karp~"
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
					"patching_rect" : [ 7.5, 67.0, 233.0, 30.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 7.5, 67.0, 221.0, 30.0 ],
					"text" : "String and Hybrid Models"
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
					"source" : [ "obj-178", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-179", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-183", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-184", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-197", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-2", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-34", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-59", 0 ]
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
