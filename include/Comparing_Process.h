//file for updating repo to main branch head
//process order compare this repo with main to find all places changes need to be made
//either edit this repo with the portion of changes to add to linux dist repo and replace linux files
//or copy from main repo.
//build test and commit, THEN fetch remote and hard reset onto this repo, to properly update
//and clear change list, for easy tracking of files to be moved for commit.
/*
* Will need to do piece meal updates not entire files but portions
* 
* 1.Make file update -				done
* 2.Summary screen nature color -	done
* 3.Super multiplier update -		done
* .type chart -						done    -added additional type tweak chart is now finalized
* 4.species names update -			done
* 5.base stats -                    done
* 6.friendship rework -				done (missing base stats changes)
* 7.ability constant ability data  -  done
* 8.move info data file and move constants -  done
* .move effect constants update  -      done
* . then port battle moves back -       done
* .summary screen ui -                  done
* .battle ui
* .name expansion -					partial
* pokedex ui.
* removal of lg pokedex entries.
*.apparently didn't add new ability desc in pokemon summary screen update
* before computer crashed so implementation incomplete...
*.added item values back -          done
*.port battlescripts defines strings & messages -  done
*.battle script commands & macros
*.battle anim commands & macros
*.after that can attempt port battlescript 1s 2s
*
* move trainer tower data to C file so can remove data_8479668.s
*
* emerald stye naming screen. for intro, add fade in for rival rename nvm
* .change namign screens for player to load like rival,  start in center like normal
* then move off to the side and load a message box w names when asking your name
* but keep emerald style gender swap fade in
* (it alraedy exists just need to swap order, right now its the view shown
* when confirming your name) remember change starting names
* Blue for rival, Red for Male player  Green for female player (also add Fire & Leaf as Male/ Female names)
* think will potentially keep Red as a random option for female player if rom is red
* and Green asa random option for male player if rom is leaf green
* 
* 
* menu cahnges worked, but from wh;at; I can tell thre's still a strange shift/glitch
* that only occurs when I go to naming screen and then press B to return to gender select
* and select a DIFFERENT gender than the one I was using (i.e go from male to female or female to male)
* 
* kurausukun recommends "Either use print debugging or track relevant variables in gdb"
* to debug it, says it should be able to find the issue I guess I would need to 
* track the value of data[1]   as I step through the intro?
*
* didnt debug, removed destory sprite with a reverse slide seems to work as of yet haven't seen another glitch
*saw it once, unsure if because hadn't made clean, just putting off having to actually debug this -_-
* 
* #if defined(FIRERED)   
* #elif defined(LEAFGREEN)
* #endif		-use these  they are defined at run time, so don't need to use both and be equal
* 
* .move effects
* .ability effects
* .battle script
* .move animations
* . attempt setup sMonSpriteAnchorCoords x y & placement of mon sprite on pokedex screen w constants
* based on height and mon elevation will put exact arrays here shortly 
* -do this after pokedex port
* 
* save systems and graphics for later, do smaller updates first
* file constant renames will prob have to come last as it would affect everything
* so keep base names, slowly add things in, then when everything is in I can do
* renames or just simiply copy the original files in, from main repo, instead of conversion repo
* as by then it'd be the same
*/