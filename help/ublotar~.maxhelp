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
		"rect" : [ 799.0, 78.0, 990.0, 866.0 ],
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
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"hidden" : 1,
					"id" : "obj-124",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 608.0, 531.0, 47.0, 23.0 ],
					"style" : "",
					"text" : "$1 20"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"hidden" : 1,
					"id" : "obj-125",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "bang" ],
					"patching_rect" : [ 608.0, 558.0, 40.0, 23.0 ],
					"style" : "",
					"text" : "line~"
				}

			}
, 			{
				"box" : 				{
					"bubbleside" : 2,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-121",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 414.0, 394.0, 37.0, 21.0 ],
					"style" : "",
					"text" : "post"
				}

			}
, 			{
				"box" : 				{
					"bubbleside" : 2,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-120",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 365.0, 394.0, 31.0, 21.0 ],
					"style" : "",
					"text" : "pre"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"hidden" : 1,
					"id" : "obj-115",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 460.0, 394.0, 47.0, 23.0 ],
					"style" : "",
					"text" : "$1 20"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"hidden" : 1,
					"id" : "obj-116",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "bang" ],
					"patching_rect" : [ 460.0, 421.0, 40.0, 23.0 ],
					"style" : "",
					"text" : "line~"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"hidden" : 1,
					"id" : "obj-113",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 310.0, 394.0, 47.0, 23.0 ],
					"style" : "",
					"text" : "$1 20"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"hidden" : 1,
					"id" : "obj-114",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "bang" ],
					"patching_rect" : [ 310.0, 421.0, 40.0, 23.0 ],
					"style" : "",
					"text" : "line~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-107",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 396.5, 202.0, 24.0, 24.0 ],
					"style" : ""
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
					"patching_rect" : [ 424.5, 203.5, 71.0, 23.0 ],
					"style" : "",
					"text" : "power $1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"hidden" : 1,
					"id" : "obj-5",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 585.0, 123.0, 162.0, 23.0 ],
					"style" : "",
					"text" : "expr (1.-$f1/127.) * 8"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"hidden" : 1,
					"id" : "obj-6",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 755.0, 123.0, 52.0, 23.0 ],
					"style" : "",
					"text" : "/ 12.7"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"hidden" : 1,
					"id" : "obj-7",
					"maxclass" : "newobj",
					"numinlets" : 3,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 587.5, 162.0, 157.0, 23.0 ],
					"style" : "",
					"text" : "sprintf pluck %i %f %i"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"hidden" : 1,
					"id" : "obj-8",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 482.5, 162.0, 35.0, 23.0 ],
					"style" : "",
					"text" : "- 1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"hidden" : 1,
					"id" : "obj-99",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 521.5, 162.0, 57.0, 23.0 ],
					"style" : "",
					"text" : "pipe 50"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"hidden" : 1,
					"id" : "obj-10",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 360.0, 123.0, 40.0, 23.0 ],
					"style" : "",
					"text" : "mtof"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"hidden" : 1,
					"id" : "obj-11",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 6,
					"outlettype" : [ "", "", "", "", "", "" ],
					"patching_rect" : [ 363.0, 162.0, 105.0, 23.0 ],
					"style" : "",
					"text" : "gate 6"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"hidden" : 1,
					"id" : "obj-12",
					"maxclass" : "newobj",
					"numinlets" : 5,
					"numoutlets" : 4,
					"outlettype" : [ "int", "", "", "int" ],
					"patching_rect" : [ 482.5, 123.0, 91.0, 23.0 ],
					"style" : "",
					"text" : "counter 1 6"
				}

			}
, 			{
				"box" : 				{
					"blackkeycolor" : [ 0.0, 0.0, 0.0, 1.0 ],
					"hkeycolor" : [ 0.501961, 0.501961, 0.501961, 1.0 ],
					"id" : "obj-13",
					"maxclass" : "kslider",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "int", "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 15.0, 123.0, 336.0, 53.0 ],
					"presentation_rect" : [ 45.0, 45.0, 336.0, 54.0 ],
					"style" : "",
					"whitekeycolor" : [ 1.0, 1.0, 1.0, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"format" : 6,
					"id" : "obj-14",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 361.0, 558.0, 63.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-100",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 361.0, 588.0, 117.0, 23.0 ],
					"style" : "",
					"text" : "setsustain -1 $1"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-16",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 428.0, 558.0, 141.0, 25.0 ],
					"style" : "",
					"text" : "\"sustain\" of strings"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"hidden" : 1,
					"id" : "obj-17",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "float" ],
					"patching_rect" : [ 594.5, 730.0, 34.0, 23.0 ],
					"style" : "",
					"text" : "t b f"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"hidden" : 1,
					"id" : "obj-18",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 516.5, 730.0, 72.0, 23.0 ],
					"style" : "",
					"text" : "pack 1. 1."
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
					"patching_rect" : [ 656.5, 695.0, 65.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"format" : 6,
					"id" : "obj-20",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 656.5, 659.0, 65.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"hidden" : 1,
					"id" : "obj-21",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 516.5, 763.0, 100.0, 23.0 ],
					"style" : "",
					"text" : "vibrato $1 $2"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-101",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 104.5, 435.0, 202.0, 25.0 ],
					"style" : "",
					"text" : "pluck string# amplitude squish"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-102",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 723.5, 589.0, 158.0, 40.0 ],
					"style" : "",
					"text" : "noise gain, associated with breath pressure"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"bubbleside" : 0,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-24",
					"linecount" : 6,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 42.375, 499.5, 225.25, 113.0 ],
					"style" : "",
					"text" : "squish, from the original cmix implementation of Sullivan's electric guitar model, lowpasses the random loading of the delay line, softening the pluck. the higher the number, the squishier."
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-25",
					"maxclass" : "number",
					"maximum" : 5,
					"minimum" : 0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 55.0, 435.0, 39.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-26",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 55.0, 467.0, 102.0, 23.0 ],
					"style" : "",
					"text" : "pluck $1 10. 2"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"format" : 6,
					"id" : "obj-29",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 656.5, 489.0, 39.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-30",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 656.5, 519.0, 61.0, 23.0 ],
					"style" : "",
					"text" : "limit $1"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"format" : 6,
					"id" : "obj-31",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 656.5, 589.0, 53.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
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
					"patching_rect" : [ 656.5, 624.0, 61.0, 23.0 ],
					"style" : "",
					"text" : "noise $1"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"format" : 6,
					"id" : "obj-33",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 656.5, 558.0, 79.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"format" : 6,
					"id" : "obj-34",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 656.5, 421.0, 39.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-35",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 656.5, 451.0, 101.0, 23.0 ],
					"style" : "",
					"text" : "distortgain $1"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-36",
					"maxclass" : "number",
					"maximum" : 5,
					"minimum" : 0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 55.0, 363.0, 39.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-37",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 308.0, 267.0, 47.0, 23.0 ],
					"style" : "",
					"text" : "$1 20"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-38",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "bang" ],
					"patching_rect" : [ 308.0, 294.0, 40.0, 23.0 ],
					"style" : "",
					"text" : "line~"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"format" : 6,
					"id" : "obj-39",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 308.0, 234.0, 57.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-40",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 250.0, 268.0, 49.0, 23.0 ],
					"style" : "",
					"text" : "$1 20"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-41",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "bang" ],
					"patching_rect" : [ 250.0, 295.0, 40.0, 23.0 ],
					"style" : "",
					"text" : "line~"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"format" : 6,
					"id" : "obj-42",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 250.0, 234.0, 51.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-43",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 192.0, 267.0, 47.0, 23.0 ],
					"style" : "",
					"text" : "$1 20"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-44",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "bang" ],
					"patching_rect" : [ 192.0, 294.0, 40.0, 23.0 ],
					"style" : "",
					"text" : "line~"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"format" : 6,
					"id" : "obj-103",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 192.0, 234.0, 51.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-46",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 134.0, 268.0, 47.0, 23.0 ],
					"style" : "",
					"text" : "$1 20"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-47",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "bang" ],
					"patching_rect" : [ 134.0, 295.0, 40.0, 23.0 ],
					"style" : "",
					"text" : "line~"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"format" : 6,
					"id" : "obj-48",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 134.0, 234.0, 51.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
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
					"patching_rect" : [ 76.0, 267.0, 47.0, 23.0 ],
					"style" : "",
					"text" : "$1 20"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-50",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "bang" ],
					"patching_rect" : [ 76.0, 294.0, 40.0, 23.0 ],
					"style" : "",
					"text" : "line~"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"format" : 6,
					"id" : "obj-51",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 76.0, 234.0, 51.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-52",
					"maxclass" : "preset",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "preset", "int", "preset", "int" ],
					"patching_rect" : [ 414.0, 263.0, 54.0, 54.0 ],
					"preset_data" : [ 						{
							"number" : 1,
							"data" : [ 5, "obj-71", "number", "float", 400.0, 6, "<invalid>", "gain~", "list", 109, 10.0, 5, "obj-66", "number", "float", 0.0, 5, "obj-65", "number", "float", 50.0, 5, "obj-58", "number", "float", 1.0, 5, "obj-55", "number", "float", 0.0, 5, "obj-53", "number", "float", 0.0, 5, "obj-51", "number", "float", 600.0, 5, "obj-48", "number", "float", 800.0, 5, "obj-45", "number", "float", 500.0, 5, "obj-42", "number", "float", 700.0, 5, "obj-39", "number", "float", 900.0, 5, "obj-36", "number", "int", 3, 5, "obj-34", "number", "float", 1.0, 5, "obj-33", "number", "float", 0.0, 5, "obj-31", "number", "float", 0.0, 5, "obj-29", "number", "float", 10.0, 5, "obj-25", "number", "int", 0, 5, "obj-20", "number", "float", 0.96, 5, "obj-19", "number", "float", 0.32, 5, "obj-14", "number", "float", 0.98 ]
						}
, 						{
							"number" : 2,
							"data" : [ 5, "obj-71", "number", "float", 400.0, 6, "<invalid>", "gain~", "list", 115, 10.0, 5, "obj-66", "number", "float", 0.0, 5, "obj-65", "number", "float", 50.0, 5, "obj-58", "number", "float", 0.0, 5, "obj-55", "number", "float", 1.0, 5, "obj-53", "number", "float", 1.0, 5, "obj-51", "number", "float", 600.0, 5, "obj-48", "number", "float", 800.0, 5, "obj-45", "number", "float", 500.0, 5, "obj-42", "number", "float", 700.0, 5, "obj-39", "number", "float", 900.0, 5, "obj-36", "number", "int", 5, 5, "obj-34", "number", "float", 1.0, 5, "obj-33", "number", "float", 0.0, 5, "obj-31", "number", "float", 0.0, 5, "obj-29", "number", "float", 10.0, 5, "obj-25", "number", "int", 0, 5, "obj-20", "number", "float", 0.96, 5, "obj-19", "number", "float", 0.32, 5, "obj-14", "number", "float", 0.98 ]
						}
, 						{
							"number" : 3,
							"data" : [ 5, "obj-71", "number", "float", 378.0, 6, "<invalid>", "gain~", "list", 97, 10.0, 5, "obj-66", "number", "float", 0.07, 5, "obj-65", "number", "float", 598.0, 5, "obj-58", "number", "float", 1.0, 5, "obj-55", "number", "float", 0.0, 5, "obj-53", "number", "float", 0.0, 5, "obj-51", "number", "float", 789.0, 5, "obj-48", "number", "float", 582.0, 5, "obj-45", "number", "float", 451.0, 5, "obj-42", "number", "float", 570.0, 5, "obj-39", "number", "float", 800.0, 5, "obj-36", "number", "int", 5, 5, "obj-34", "number", "float", 1.0, 5, "obj-33", "number", "float", 1.17, 5, "obj-31", "number", "float", 1.0, 5, "obj-29", "number", "float", 10.0, 5, "obj-25", "number", "int", 0, 5, "obj-20", "number", "float", 0.99, 5, "obj-19", "number", "float", 0.32, 5, "obj-14", "number", "float", 0.98 ]
						}
, 						{
							"number" : 4,
							"data" : [ 5, "obj-71", "number", "float", 195.997711, 6, "<invalid>", "gain~", "list", 109, 10.0, 5, "obj-66", "number", "float", 0.5, 5, "obj-65", "number", "float", 59.0, 5, "obj-58", "number", "float", 0.5, 5, "obj-55", "number", "float", 1.0, 5, "obj-53", "number", "float", 1.0, 5, "obj-51", "number", "float", 246.94165, 5, "obj-48", "number", "float", 329.627563, 5, "obj-45", "number", "float", 82.406891, 5, "obj-42", "number", "float", 110.0, 5, "obj-39", "number", "float", 146.832382, 5, "obj-36", "number", "int", 2, 5, "obj-34", "number", "float", 1.0, 5, "obj-33", "number", "float", 1.26, 5, "obj-31", "number", "float", 0.05, 5, "obj-29", "number", "float", 10.0, 5, "obj-25", "number", "int", 0, 5, "obj-20", "number", "float", 4.0, 5, "obj-19", "number", "float", 0.06, 5, "obj-14", "number", "float", 0.5, 5, "obj-13", "kslider", "int", 64 ]
						}
, 						{
							"number" : 5,
							"data" : [ 5, "obj-71", "number", "float", 293.664764, 6, "<invalid>", "gain~", "list", 98, 10.0, 5, "obj-66", "number", "float", 0.37, 5, "obj-65", "number", "float", 53.110001, 5, "obj-58", "number", "float", 1.0, 5, "obj-55", "number", "float", 1.0, 5, "obj-53", "number", "float", 1.0, 5, "obj-51", "number", "float", 391.995422, 5, "obj-48", "number", "float", 493.883301, 5, "obj-45", "number", "float", 659.255127, 5, "obj-42", "number", "float", 164.813782, 5, "obj-39", "number", "float", 220.0, 5, "obj-36", "number", "int", 0, 5, "obj-34", "number", "float", 1.0, 5, "obj-33", "number", "float", 0.74, 5, "obj-31", "number", "float", 0.09, 5, "obj-29", "number", "float", 10.0, 5, "obj-25", "number", "int", 5, 5, "obj-20", "number", "float", 4.0, 5, "obj-19", "number", "float", 0.06, 5, "obj-14", "number", "float", 0.99, 5, "obj-13", "kslider", "int", 76 ]
						}
, 						{
							"number" : 6,
							"data" : [ 5, "obj-71", "number", "float", 100.0, 6, "<invalid>", "gain~", "list", 98, 10.0, 5, "obj-66", "number", "float", 0.02, 5, "obj-65", "number", "float", 209.0, 5, "obj-58", "number", "float", 1.0, 5, "obj-55", "number", "float", 1.0, 5, "obj-53", "number", "float", 1.0, 5, "obj-51", "number", "float", 300.0, 5, "obj-48", "number", "float", 500.0, 5, "obj-45", "number", "float", 200.0, 5, "obj-42", "number", "float", 400.0, 5, "obj-39", "number", "float", 600.0, 5, "obj-36", "number", "int", 5, 5, "obj-34", "number", "float", 10.0, 5, "obj-33", "number", "float", 0.0, 5, "obj-31", "number", "float", 0.02, 5, "obj-29", "number", "float", 10.0, 5, "obj-25", "number", "int", 5, 5, "obj-20", "number", "float", 0.98, 5, "obj-19", "number", "float", 0.06, 5, "obj-14", "number", "float", 0.99, 5, "obj-13", "kslider", "int", 76 ]
						}
, 						{
							"number" : 7,
							"data" : [ 5, "obj-71", "number", "float", 440.0, 6, "<invalid>", "gain~", "list", 98, 10.0, 5, "obj-66", "number", "float", 0.43, 5, "obj-65", "number", "float", 209.0, 5, "obj-58", "number", "float", 1.0, 5, "obj-55", "number", "float", 1.0, 5, "obj-53", "number", "float", 0.01, 5, "obj-51", "number", "float", 261.62558, 5, "obj-48", "number", "float", 110.0, 5, "obj-45", "number", "float", 493.883301, 5, "obj-42", "number", "float", 246.94165, 5, "obj-39", "number", "float", 659.255127, 5, "obj-36", "number", "int", 5, 5, "obj-34", "number", "float", 2.0, 5, "obj-33", "number", "float", 0.87, 5, "obj-31", "number", "float", 0.13, 5, "obj-29", "number", "float", 10.0, 5, "obj-25", "number", "int", 5, 5, "obj-20", "number", "float", 3.0, 5, "obj-19", "number", "float", 0.85, 5, "obj-14", "number", "float", 0.99, 5, "obj-13", "kslider", "int", 59 ]
						}
, 						{
							"number" : 8,
							"data" : [ 5, "obj-71", "number", "float", 87.30706, 6, "<invalid>", "gain~", "list", 98, 10.0, 5, "obj-66", "number", "float", 0.43, 5, "obj-65", "number", "float", 209.0, 5, "obj-58", "number", "float", 1.0, 5, "obj-55", "number", "float", 1.0, 5, "obj-53", "number", "float", 0.01, 5, "obj-51", "number", "float", 220.0, 5, "obj-48", "number", "float", 523.25116, 5, "obj-45", "number", "float", 830.609375, 5, "obj-42", "number", "float", 103.826172, 5, "obj-39", "number", "float", 82.406891, 5, "obj-36", "number", "int", 5, 5, "obj-34", "number", "float", 2.0, 5, "obj-33", "number", "float", 0.87, 5, "obj-31", "number", "float", 0.13, 5, "obj-29", "number", "float", 10.0, 5, "obj-25", "number", "int", 5, 5, "obj-20", "number", "float", 3.0, 5, "obj-19", "number", "float", 0.85, 5, "obj-14", "number", "float", 0.99, 5, "obj-13", "kslider", "int", 80 ]
						}
, 						{
							"number" : 9,
							"data" : [ 5, "obj-71", "number", "float", 155.563492, 6, "<invalid>", "gain~", "list", 97, 10.0, 5, "obj-66", "number", "float", 0.24, 5, "obj-65", "number", "float", 223.0, 5, "obj-58", "number", "float", 0.44, 5, "obj-55", "number", "float", 0.75, 5, "obj-53", "number", "float", 0.0, 5, "obj-51", "number", "float", 92.498604, 5, "obj-48", "number", "float", 246.94165, 5, "obj-45", "number", "float", 329.627563, 5, "obj-42", "number", "float", 659.255127, 5, "obj-39", "number", "float", 880.0, 5, "obj-36", "number", "int", 0, 5, "obj-34", "number", "float", 1.0, 5, "obj-33", "number", "float", 0.0, 5, "obj-31", "number", "float", 1.0, 5, "obj-29", "number", "float", 79.0, 5, "obj-25", "number", "int", 0, 5, "obj-20", "number", "float", 1.0, 5, "obj-19", "number", "float", 0.46, 5, "obj-14", "number", "float", 0.995, 5, "obj-13", "kslider", "int", 42 ]
						}
, 						{
							"number" : 10,
							"data" : [ 5, "obj-71", "number", "float", 830.609375, 6, "<invalid>", "gain~", "list", 98, 10.0, 5, "obj-66", "number", "float", 0.06, 5, "obj-65", "number", "float", 169.0, 5, "obj-58", "number", "float", 1.0, 5, "obj-55", "number", "float", 1.0, 5, "obj-53", "number", "float", 1.0, 5, "obj-51", "number", "float", 880.0, 5, "obj-48", "number", "float", 880.0, 5, "obj-45", "number", "float", 440.0, 5, "obj-42", "number", "float", 220.0, 5, "obj-39", "number", "float", 116.540939, 5, "obj-36", "number", "int", 5, 5, "obj-34", "number", "float", 10.0, 5, "obj-33", "number", "float", 0.08, 5, "obj-31", "number", "float", 0.02, 5, "obj-29", "number", "float", 10.0, 5, "obj-25", "number", "int", 5, 5, "obj-20", "number", "float", 4.0, 5, "obj-19", "number", "float", 0.06, 5, "obj-14", "number", "float", 0.99, 5, "obj-13", "kslider", "int", 46 ]
						}
, 						{
							"number" : 11,
							"data" : [ 5, "obj-71", "number", "float", 830.609375, 6, "<invalid>", "gain~", "list", 98, 10.0, 5, "obj-66", "number", "float", 0.76, 5, "obj-65", "number", "float", 117.0, 5, "obj-58", "number", "float", 1.0, 5, "obj-55", "number", "float", 1.0, 5, "obj-53", "number", "float", 0.73, 5, "obj-51", "number", "float", 116.540939, 5, "obj-48", "number", "float", 880.0, 5, "obj-45", "number", "float", 440.0, 5, "obj-42", "number", "float", 220.0, 5, "obj-39", "number", "float", 116.540939, 5, "obj-36", "number", "int", 5, 5, "obj-34", "number", "float", 10.0, 5, "obj-33", "number", "float", 0.09, 5, "obj-31", "number", "float", 0.02, 5, "obj-29", "number", "float", 10.0, 5, "obj-25", "number", "int", 5, 5, "obj-20", "number", "float", 4.0, 5, "obj-19", "number", "float", 0.06, 5, "obj-14", "number", "float", 0.99, 5, "obj-13", "kslider", "int", 46 ]
						}
, 						{
							"number" : 12,
							"data" : [ 5, "obj-71", "number", "float", 130.81279, 6, "<invalid>", "gain~", "list", 98, 10.0, 5, "obj-66", "number", "float", 0.76, 5, "obj-65", "number", "float", 89.0, 5, "obj-58", "number", "float", 1.0, 5, "obj-55", "number", "float", 1.0, 5, "obj-53", "number", "float", 0.73, 5, "obj-51", "number", "float", 87.30706, 5, "obj-48", "number", "float", 246.94165, 5, "obj-45", "number", "float", 391.995422, 5, "obj-42", "number", "float", 261.62558, 5, "obj-39", "number", "float", 329.627563, 5, "obj-36", "number", "int", 5, 5, "obj-34", "number", "float", 10.0, 5, "obj-33", "number", "float", 0.09, 5, "obj-31", "number", "float", 0.02, 5, "obj-29", "number", "float", 10.0, 5, "obj-25", "number", "int", 5, 5, "obj-20", "number", "float", 4.0, 5, "obj-19", "number", "float", 0.06, 5, "obj-14", "number", "float", 0.99, 5, "obj-13", "kslider", "int", 60 ]
						}
, 						{
							"number" : 13,
							"data" : [ 5, "obj-71", "number", "float", 261.62558, 6, "<invalid>", "gain~", "list", 98, 10.0, 5, "obj-66", "number", "float", 0.76, 5, "obj-65", "number", "float", 60.0, 5, "obj-58", "number", "float", 1.0, 5, "obj-55", "number", "float", 1.0, 5, "obj-53", "number", "float", 0.73, 5, "obj-51", "number", "float", 87.30706, 5, "obj-48", "number", "float", 246.94165, 5, "obj-45", "number", "float", 391.995422, 5, "obj-42", "number", "float", 261.62558, 5, "obj-39", "number", "float", 329.627563, 5, "obj-36", "number", "int", 5, 5, "obj-34", "number", "float", 10.0, 5, "obj-33", "number", "float", 0.09, 5, "obj-31", "number", "float", 0.02, 5, "obj-29", "number", "float", 10.0, 5, "obj-25", "number", "int", 5, 5, "obj-20", "number", "float", 4.0, 5, "obj-19", "number", "float", 0.06, 5, "obj-14", "number", "float", 0.99, 5, "obj-13", "kslider", "int", 60, 5, "<invalid>", "toggle", "int", 1 ]
						}
, 						{
							"number" : 14,
							"data" : [ 5, "obj-71", "number", "float", 261.62558, 6, "<invalid>", "gain~", "list", 98, 10.0, 5, "obj-66", "number", "float", 0.99, 5, "obj-65", "number", "float", 46.0, 5, "obj-58", "number", "float", 1.0, 5, "obj-55", "number", "float", 1.0, 5, "obj-53", "number", "float", 0.55, 5, "obj-51", "number", "float", 87.30706, 5, "obj-48", "number", "float", 246.94165, 5, "obj-45", "number", "float", 391.995422, 5, "obj-42", "number", "float", 261.62558, 5, "obj-39", "number", "float", 261.62558, 5, "obj-36", "number", "int", 5, 5, "obj-34", "number", "float", 10.0, 5, "obj-33", "number", "float", 0.09, 5, "obj-31", "number", "float", 0.02, 5, "obj-29", "number", "float", 10.0, 5, "obj-25", "number", "int", 5, 5, "obj-20", "number", "float", 4.0, 5, "obj-19", "number", "float", 0.06, 5, "obj-14", "number", "float", 0.99, 5, "obj-13", "kslider", "int", 60, 5, "<invalid>", "toggle", "int", 1 ]
						}
, 						{
							"number" : 15,
							"data" : [ 5, "obj-71", "number", "float", 65.406395, 6, "<invalid>", "gain~", "list", 98, 10.0, 5, "obj-66", "number", "float", 0.43, 5, "obj-65", "number", "float", 49.0, 5, "obj-58", "number", "float", 1.0, 5, "obj-55", "number", "float", 1.0, 5, "obj-53", "number", "float", 0.01, 5, "obj-51", "number", "float", 69.295654, 5, "obj-48", "number", "float", 73.416191, 5, "obj-45", "number", "float", 77.781746, 5, "obj-42", "number", "float", 82.406891, 5, "obj-39", "number", "float", 87.30706, 5, "obj-36", "number", "int", 5, 5, "obj-34", "number", "float", 2.0, 5, "obj-33", "number", "float", 0.87, 5, "obj-31", "number", "float", 0.13, 5, "obj-29", "number", "float", 10.0, 5, "obj-25", "number", "int", 5, 5, "obj-20", "number", "float", 3.0, 5, "obj-19", "number", "float", 0.45, 5, "obj-14", "number", "float", 0.99, 5, "obj-13", "kslider", "int", 41, 5, "<invalid>", "toggle", "int", 1 ]
						}
 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"format" : 6,
					"id" : "obj-53",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 361.0, 623.0, 39.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-54",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 361.0, 657.0, 139.0, 23.0 ],
					"style" : "",
					"text" : "lowpasscross -1 $1"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"format" : 6,
					"id" : "obj-55",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 413.0, 421.0, 39.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"format" : 6,
					"id" : "obj-58",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 361.0, 421.0, 39.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-61",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 18.0, 268.0, 47.0, 23.0 ],
					"style" : "",
					"text" : "$1 20"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-62",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "bang" ],
					"patching_rect" : [ 18.0, 295.0, 40.0, 23.0 ],
					"style" : "",
					"text" : "line~"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"hidden" : 1,
					"id" : "obj-63",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 310.0, 455.0, 50.0, 23.0 ],
					"style" : "",
					"text" : "$1 200"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"hidden" : 1,
					"id" : "obj-64",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "bang" ],
					"patching_rect" : [ 310.0, 491.0, 40.0, 23.0 ],
					"style" : "",
					"text" : "line~"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"format" : 6,
					"id" : "obj-65",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 361.0, 455.0, 112.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"format" : 6,
					"id" : "obj-66",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 361.0, 491.0, 54.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-67",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 361.0, 520.0, 83.0, 23.0 ],
					"style" : "",
					"text" : "feedgain $1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-68",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 55.0, 395.0, 91.0, 23.0 ],
					"style" : "",
					"text" : "pluck $1 10."
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.290196, 0.309804, 0.301961, 1.0 ],
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"format" : 6,
					"id" : "obj-71",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 18.0, 234.0, 51.0, 23.0 ],
					"style" : "",
					"textcolor" : [ 0.921569, 0.917647, 0.933333, 1.0 ],
					"triscale" : 0.9
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-72",
					"maxclass" : "newobj",
					"numinlets" : 10,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 18.0, 324.0, 450.0, 23.0 ],
					"style" : "",
					"text" : "ublotar~"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-74",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 99.0, 363.0, 160.0, 25.0 ],
					"style" : "",
					"text" : "pluck string# amplitude"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"bubbleside" : 2,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-75",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 361.0, 363.0, 91.0, 40.0 ],
					"style" : "",
					"text" : "Output Gains"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-76",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 482.0, 455.0, 141.0, 25.0 ],
					"style" : "",
					"text" : "feedback frequency"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-77",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 421.0, 491.0, 108.0, 25.0 ],
					"style" : "",
					"text" : "feedback gain"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-78",
					"linecount" : 4,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 502.0, 613.0, 146.0, 69.0 ],
					"style" : "",
					"text" : "crossfade between lowpass filter types. 1. is more flute-like;\r0. is more guitar-like."
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"bubbleside" : 0,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-79",
					"linecount" : 6,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 299.0, 689.0, 210.0, 113.0 ],
					"style" : "",
					"text" : "first argument of -1 sends this value to all strings. otherwise you can control this for each string individually by setting the first argument to the string number (0-5)"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-80",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 704.5, 421.0, 240.0, 25.0 ],
					"style" : "",
					"text" : "how hard to drive the preamp, sort of"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-81",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 723.5, 489.0, 209.0, 54.0 ],
					"style" : "",
					"text" : "limiter threshold, to keep things from completely blowing up. this is internal to each string."
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-82",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 740.0, 558.0, 119.0, 25.0 ],
					"style" : "",
					"text" : "breath pressure"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"bubbleside" : 2,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-83",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 103.5, 186.0, 159.0, 40.0 ],
					"style" : "",
					"text" : "STRING FREQUENCIES"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-85",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 730.0, 659.0, 127.0, 25.0 ],
					"style" : "",
					"text" : "vibrato frequency"
				}

			}
, 			{
				"box" : 				{
					"bubble" : 1,
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-86",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 730.0, 695.0, 95.0, 25.0 ],
					"style" : "",
					"text" : "vibrato gain"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-87",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 396.5, 234.0, 89.0, 21.0 ],
					"style" : "",
					"text" : "some presets"
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
					"patching_rect" : [ 22.625, 759.0, 136.0, 48.0 ],
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
					"patching_rect" : [ 22.625, 817.0, 45.0, 45.0 ],
					"style" : ""
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 13.0,
					"id" : "obj-22",
					"linecount" : 3,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 4.0, 62.0, 562.0, 50.0 ],
					"style" : "",
					"text" : "the UBLOTAR, a new version of the blotar that has six strings/bores, feeding a single distortion and by $2, with controls for pre/post distortion output gains (so you can mix them), predistortion gain (drive?), and all the same old flute controls (breath pressure, etc....)",
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
					"text" : "ublotar~",
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
					"patching_rect" : [ 845.125, 730.0, 140.0, 87.0 ],
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
					"patching_rect" : [ 610.125, 826.0, 375.0, 21.0 ],
					"style" : "",
					"text" : "• by dan trueman, music department princeton university"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-11", 1 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-10", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-72", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-100", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-43", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-103", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-4", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-107", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-103", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-11", 3 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-11", 5 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-42", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-11", 4 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-48", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-11", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-51", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-11", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-71", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-11", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-114", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-113", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-72", 7 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-114", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-116", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-115", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-72", 8 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-116", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-11", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-12", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-12", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-125", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-124", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-72", 9 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-125", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-5", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-13", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-13", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-100", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 1 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-17", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-20", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-17", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-21", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-18", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-17", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-19", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-20", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-72", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-21", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-26", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-25", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-72", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-26", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-29", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-72", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-30", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-32", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-31", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-72", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-32", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-124", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-33", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-35", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-72", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-35", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-68", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-36", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-38", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-37", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-72", 5 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-38", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-37", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-39", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-72", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-41", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-40", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-72", 4 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-40", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-42", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-43", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-72", 3 ],
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
					"destination" : [ "obj-47", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-46", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-72", 2 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-47", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-46", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-48", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-50", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-49", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 2 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-72", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-50", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-49", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-51", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-54", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-53", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-72", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-54", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-115", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-55", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-113", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-58", 0 ]
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
					"destination" : [ "obj-62", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-61", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-72", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-62", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-64", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-63", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-72", 6 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-64", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-63", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-65", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-67", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-66", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-72", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-67", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-72", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-68", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-72", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-7", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-61", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-71", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-45", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-72", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-99", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"disabled" : 0,
					"hidden" : 1,
					"source" : [ "obj-99", 0 ]
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
				"patcherrelativepath" : "../../../../../../Shared/Max 7/Packages/PeRColate/media",
				"type" : "JPEG",
				"implicit" : 1
			}
, 			{
				"name" : "ublotar~.mxo",
				"type" : "iLaX"
			}
 ],
		"embedsnapshot" : 0
	}

}
