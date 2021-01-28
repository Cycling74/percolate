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
		"rect" : [ 73.0, 107.0, 945.0, 663.0 ],
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
					"id" : "obj-55",
					"maxclass" : "fpic",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "jit_matrix" ],
					"patching_rect" : [ 29.0, 30.0, 140.0, 87.0 ],
					"pic" : "percolate.jpg",
					"presentation" : 1,
					"presentation_rect" : [ 778.618113160133362, 12.0, 134.881886839866638, 78.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-24",
					"linecount" : 2,
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 187.5, 419.61562043428421, 325.0, 35.0 ],
					"text" : ";\rmax launchbrowser https://ccrma.stanford.edu/software/stk/"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.156862745098039, 0.156862745098039, 0.156862745098039, 1.0 ],
					"fontname" : "Lato",
					"id" : "obj-25",
					"maxclass" : "textbutton",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 187.5, 388.0, 80.381886839866638, 22.61562043428421 ],
					"presentation" : 1,
					"presentation_rect" : [ 230.5, 386.0, 87.0, 24.0 ],
					"rounded" : 8.0,
					"text" : "Website",
					"texton" : "Website",
					"textoncolor" : [ 0.839216, 0.882353, 0.886275, 1.0 ],
					"truncate" : 0
				}

			}
, 			{
				"box" : 				{
					"fontface" : 2,
					"fontname" : "Lato",
					"fontsize" : 10.0,
					"id" : "obj-23",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 604.5, 632.800252437591553, 323.0, 18.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 824.618113160133362, 516.800252437591553, 70.0, 18.0 ],
					"text" : "- Dan Trueman"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 2,
					"fontname" : "Lato",
					"fontsize" : 10.0,
					"id" : "obj-22",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 98.5, 674.800252437591553, 323.0, 18.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 248.5, 631.800252437591553, 188.0, 18.0 ],
					"text" : "- https://ccrma.stanford.edu/software/stk/"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-20",
					"linecount" : 2,
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 604.5, 351.0, 309.0, 35.0 ],
					"text" : ";\rmax launchbrowser http://www.music.columbia.edu/cmix"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.156862745098039, 0.156862745098039, 0.156862745098039, 1.0 ],
					"fontname" : "Lato",
					"id" : "obj-21",
					"maxclass" : "textbutton",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 604.5, 319.38437956571579, 80.381886839866638, 22.61562043428421 ],
					"presentation" : 1,
					"presentation_rect" : [ 645.5, 383.0, 87.0, 24.0 ],
					"rounded" : 8.0,
					"text" : "Website",
					"texton" : "Website",
					"textoncolor" : [ 0.839216, 0.882353, 0.886275, 1.0 ],
					"truncate" : 0
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-19",
					"linecount" : 7,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 474.5, 424.0, 407.0, 107.0 ],
					"presentation" : 1,
					"presentation_linecount" : 6,
					"presentation_rect" : [ 481.618113160133362, 417.0, 434.0, 93.0 ],
					"text" : "RTcmix is an open-source synthesis and signal-processing package based on Paul Lansky's CMIX software, which was developed at Princeton University in the 1980's. It runs on Linux and Irix, and is maintained by Brad Garton (at Columbia University) and Dave Topper (at the University of Virginia). It allows for real-time score processing, event streaming over TCP/IP, and has examples for interfacing parsers in C/C++ and Lisp, as well as interfaces in X/Motif."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Futura Bold",
					"fontsize" : 18.0,
					"id" : "obj-17",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 474.5, 388.0, 156.0, 30.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 481.618113160133362, 380.0, 156.0, 30.0 ],
					"text" : "Real-Time Cmix"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-16",
					"linecount" : 14,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 9.5, 468.0, 404.0, 208.0 ],
					"presentation" : 1,
					"presentation_linecount" : 14,
					"presentation_rect" : [ 14.5, 420.0, 428.0, 208.0 ],
					"text" : "The Synthesis ToolKit in C++ (STK) is a set of open source audio signal processing and algorithmic synthesis classes written in the C++ programming language. STK was designed to facilitate rapid development of music synthesis and audio processing software, with an emphasis on cross-platform functionality, realtime control, ease of use, and educational example code. The Synthesis ToolKit is extremely portable (it's mostly platform-independent C and C++ code), and it's completely user-extensible (all source included, no unusual libraries, and no hidden drivers). We like to think that this increases the chances that our programs will still work in another 5-10 years. In fact, the ToolKit has been working continuously for nearly 20 years now. STK currently runs with realtime support (audio and MIDI) on Linux, Macintosh OS X, and Windows computer platforms. Generic, non-realtime support has been tested under NeXTStep, Sun, and other platforms and should work with any standard C++ compiler."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Futura Bold",
					"fontsize" : 18.0,
					"id" : "obj-14",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 9.5, 424.0, 209.0, 30.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 14.5, 383.0, 223.0, 30.0 ],
					"text" : "The Synthesis Toolkit"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 2,
					"fontname" : "Lato",
					"fontsize" : 10.0,
					"id" : "obj-13",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 703.5, 276.800252437591553, 323.0, 18.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 785.618113160133362, 290.0, 109.0, 18.0 ],
					"text" : "- http://lukedubois.com/"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 2,
					"fontname" : "Lato",
					"fontsize" : 10.0,
					"id" : "obj-12",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 89.5, 340.800252437591553, 323.0, 18.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 248.5, 317.800252437591553, 188.0, 18.0 ],
					"text" : "- http://manyarrowsmusic.com/about.html"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-11",
					"linecount" : 13,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 12.5, 139.800252437591553, 400.0, 194.0 ],
					"presentation" : 1,
					"presentation_linecount" : 12,
					"presentation_rect" : [ 14.5, 132.0, 429.0, 179.0 ],
					"text" : "Dan Trueman is a musician: a fiddler, a collaborator, a teacher, a developer of new instruments, a composer of music for ensembles of all shapes and sizes. He has worked with ensembles such as So Percussion, the PRISM Quartet, Eighth Blackbird, Gallicantus, the JACK Quartet, as well as individuals like scientist Naomi Leonard, choreographer Rebecca Lazier, poet Paul Muldoon, director Mark DeChiazza, fiddler Caoimhín Ó Raghallaigh, vocalist Iarla Ó Lionáird, guitarist/songwriter Monica Mugan, and many others. Dan's work has been recognized by fellowships, grants, commissions, and awards from the Guggenheim Foundation, the Barlow Endowment, the Bessies, the Fulbright Commission, the American Composers Forum, the American Council of Learned Societies, Meet the Composer, among others. He is Professor of Music and Director of the Princeton Sound Kitchen at Princeton University."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-9",
					"linecount" : 2,
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 170.5, 84.0, 307.0, 35.0 ],
					"text" : ";\rmax launchbrowser https://www.manyarrowsmusic.com/"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.156862745098039, 0.156862745098039, 0.156862745098039, 1.0 ],
					"fontname" : "Lato",
					"id" : "obj-10",
					"maxclass" : "textbutton",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 170.5, 52.38437956571579, 80.381886839866638, 22.61562043428421 ],
					"presentation" : 1,
					"presentation_rect" : [ 165.0, 103.0, 87.0, 24.0 ],
					"rounded" : 8.0,
					"text" : "Website",
					"texton" : "Website",
					"textoncolor" : [ 0.839216, 0.882353, 0.886275, 1.0 ],
					"truncate" : 0
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-8",
					"linecount" : 2,
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 651.5, 74.0, 233.0, 35.0 ],
					"text" : ";\rmax launchbrowser http://lukedubois.com/"
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
					"patching_rect" : [ 651.5, 42.38437956571579, 80.381886839866638, 22.61562043428421 ],
					"presentation" : 1,
					"presentation_rect" : [ 645.5, 103.876911997795105, 87.0, 24.0 ],
					"rounded" : 8.0,
					"text" : "Website",
					"texton" : "Website",
					"textoncolor" : [ 0.839216, 0.882353, 0.886275, 1.0 ],
					"truncate" : 0
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Futura Bold",
					"fontsize" : 18.0,
					"id" : "obj-6",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 7.5, 79.0, 137.0, 30.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 14.5, 100.0, 138.0, 30.0 ],
					"text" : "Dan Trueman"
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
					"patching_rect" : [ 479.5, 79.0, 162.0, 30.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 481.5, 100.0, 162.0, 30.0 ],
					"text" : "R. Luke DuBois"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 0,
					"fontname" : "Lato",
					"fontsize" : 12.0,
					"id" : "obj-18",
					"linecount" : 10,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 479.5, 114.677164435386658, 400.0, 150.0 ],
					"presentation" : 1,
					"presentation_linecount" : 9,
					"presentation_rect" : [ 481.618113160133362, 137.677164435386658, 435.881886839866638, 136.0 ],
					"text" : "R. Luke DuBois is a composer, artist, and performer who explores the temporal, verbal, and visual structures of cultural and personal ephemera. He holds a doctorate in music composition from Columbia University, and has lectured and taught worldwide on interactive sound and video performance. He has collaborated on interactive performance, installation, and music production work with many artists and organizations including Toni Dove, Todd Reynolds, Chris Mann, Bora Yoon, Michael Joaquin Grey, Matthew Ritchie, Elliott Sharp, Michael Gordon, Maya Lin, Bang on a Can, Engine 27, Harvestworks, and LEMUR, and was the director of the Princeton Laptop Orchestra for its 2007 season."
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
					"patching_rect" : [ 7.5, 12.0, 126.0, 53.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 7.5, 12.0, 203.0, 53.0 ],
					"text" : "About"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-10", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 0 ],
					"source" : [ "obj-21", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-24", 0 ],
					"source" : [ "obj-25", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 0 ],
					"source" : [ "obj-31", 0 ]
				}

			}
 ],
		"dependency_cache" : [ 			{
				"name" : "percolate.jpg",
				"bootpath" : "~/Documents/Max Third Party Externals/extern-dev/percolate/media",
				"patcherrelativepath" : "../media",
				"type" : "JPEG",
				"implicit" : 1
			}
 ],
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
