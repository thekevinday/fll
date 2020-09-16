# FLL - Level 1
# Project: Colors
# Version: 0.5.1
# Licenses: flll, lgplv2.1
# Programmers: Kevin Day
# Documentation: Provide basic color output support (linux & xterm)
#                There will be future support for getting these values from a specified file, but at a higher level.
  fl_color_none=
  fl_color_reset="0"
  fl_color_bold="1"
  fl_color_underline="4"
  fl_color_blink="5"
  fl_color_highlight="7"
  fl_color_nothing="8"
  fl_color_black="30"
  fl_color_red="31"
  fl_color_green="32"
  fl_color_yellow="33"
  fl_color_blue="34"
  fl_color_purple="35"
  fl_color_teal="36"
  fl_color_white="37"
  fl_color_brightblack="90"
  fl_color_brightred="91"
  fl_color_brightgreen="92"
  fl_color_brightyellow="93"
  fl_color_brightblue="94"
  fl_color_brightpurple="95"
  fl_color_brightteal="96"
  fl_color_brightwhite="97"
  fl_color_black_bg="40"
  fl_color_red_bg="41"
  fl_color_green_bg="42"
  fl_color_yellow_bg="43"
  fl_color_blue_bg="44"
  fl_color_purple_bg="45"
  fl_color_teal_bg="46"
  fl_color_white_bg="47"
  fl_color_brightblack_bg="100"
  fl_color_brightred_bg="101"
  fl_color_brightgreen_bg="102"
  fl_color_brightyellow_bg="103"
  fl_color_brightblue_bg="104"
  fl_color_brightpurple_bg="105"
  fl_color_brightteal_bg="106"
  fl_color_brightwhite_bg="107"

  # $1 = term, $2->$6 = colors, returned = color code returned
  fl_set_color(){
    if [[ $1 == "lt" || $1 == "xt" ]] ; then
      returned="\\033["
      local hit="no"
      local fail="no"
      local tailit="no"

      for i in $2 $3 $4 $5 $6 ; do
        if [[ $1 == "xt" ]] ; then
          case $i in
            shade)
              hit="yes"
              tailit="no"
            ;;
          esac
        elif [[ $1 == "lt" ]] ; then
          case $i in
            shade)
              if [[ $tailit == "yes" ]] ; then returned="$returned;" ; fi
              returned="$returned$fl_color_blink"
              hit="yes"
              tailit="yes"
            ;;
            blink)
              hit="yes"
              tailit="no"
            ;;
            nothing)
              hit="yes"
              tailit="no"
            ;;
          esac
        fi

        if [[ $hit == "no" ]] ; then

          if [[ $tailit == "yes" ]] ; then
            returned="$returned;"
            tailit=no;
          else
            tailit=yes;
          fi

          case $i in
            reset)
              returned="$returned$fl_color_reset"
              tailit="yes"
            ;;
            bold)
              returned="$returned$fl_color_bold"
              tailit="yes"
            ;;
            underline)
              returned="$returned$fl_color_underline"
              tailit="yes"
            ;;
            blink)
              returned="$returned$fl_color_blink"
              tailit="yes"
            ;;
            highlight)
              returned="$returned$fl_color_highlight"
              tailit="yes"
            ;;
            nothing)
              returned="$returned$fl_color_nothing"
              tailit="yes"
            ;;
            black)
              returned="$returned$fl_color_black"
              tailit="yes"
            ;;
            red)
              returned="$returned$fl_color_red"
              tailit="yes"
            ;;
            green)
              returned="$returned$fl_color_green"
              tailit="yes"
            ;;
            yellow)
              returned="$returned$fl_color_yellow"
              tailit="yes"
            ;;
            blue)
              returned="$returned$fl_color_blue"
              tailit="yes"
            ;;
            purple)
              returned="$returned$fl_color_purple"
              tailit="yes"
            ;;
            teal)
              returned="$returned$fl_color_teal"
              tailit="yes"
            ;;
            white)
              returned="$returned$fl_color_white"
              tailit="yes"
            ;;
            brightblack)
              returned="$returned$fl_color_brightblack"
              tailit="yes"
            ;;
            brightred)
              returned="$returned$fl_color_brightred"
              tailit="yes"
            ;;
            brightgreen)
              returned="$returned$fl_color_brightgreen"
              tailit="yes"
            ;;
            brightyellow)
              returned="$returned$fl_color_brightyellow"
              tailit="yes"
            ;;
            brightblue)
              returned="$returned$fl_color_brightblue"
              tailit="yes"
            ;;
            brightpurple)
              returned="$returned$fl_color_brightpurple"
              tailit="yes"
            ;;
            brightteal)
              returned="$returned$fl_color_brightteal"
              tailit="yes"
            ;;
            brightwhite)
              returned="$returned$fl_color_brightwhite"
              tailit="yes"
            ;;
            black_bg)
              returned="$returned$fl_color_black_bg"
              tailit="yes"
            ;;
            red_bg)
              returned="$returned$fl_color_red_bg"
              tailit="yes"
            ;;
            green_bg)
              returned="$returned$fl_color_green_bg"
              tailit="yes"
            ;;
            yellow_bg)
              returned="$returned$fl_color_yellow_bg"
              tailit="yes"
            ;;
            blue_bg)
              returned="$returned$fl_color_blue_bg"
              tailit="yes"
            ;;
            purple_bg)
              returned="$returned$fl_color_purple_bg"
              tailit="yes"
            ;;
            teal_bg)
              returned="$returned$fl_color_teal_bg"
              tailit="yes"
            ;;
            white_bg)
              returned="$returned$fl_color_white_bg"
              tailit="yes"
            ;;
            brightblack_bg)
              returned="$returned$fl_color_brightblack_bg"
              tailit="yes"
            ;;
            brightred_bg)
              returned="$returned$fl_color_brightred_bg"
              tailit="yes"
            ;;
            brightgreen_bg)
              returned="$returned$fl_color_brightgreen_bg"
              tailit="yes"
            ;;
            brightyellow_bg)
              returned="$returned$fl_color_brightyellow_bg"
              tailit="yes"
            ;;
            brightblue_bg)
              returned="$returned$fl_color_brightblue_bg"
              tailit="yes"
            ;;
            brightpurple_bg)
              returned="$returned$fl_color_brightpurple_bg"
              tailit="yes"
            ;;
            brightteal_bg)
              returned="$returned$fl_color_brightteal_bg"
              tailit="yes"
            ;;
            brightwhite_bg)
              returned="$returned$fl_color_brightwhite_bg"
              tailit="yes"
            ;;
          esac
        fi

        hit="no"
      done

      returned="${returned}m"
    fi
  }
