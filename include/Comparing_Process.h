#define COMPARISON_FILE
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
* .battle ui -                          done
* .name expansion -					partial
* pokedex ui.
* removal of lg pokedex entries.
*.apparently didn't add new ability desc in pokemon summary screen update
* before computer crashed so implementation incomplete... *redone
*.added item values back -          done
*.port battlescripts defines strings & messages -  done
*.battle script commands & macros       -ported and updated
*.battle anim commands & macros         -done
*.after that can attempt port battlescript 1s 2s    -done
*
* move trainer tower data to C file so can remove data_8479668.s    -done
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
* .move effects     -done -mostly
* .ability effects  -done -mostly
* .battle script    -done
* .move animations - done
* . attempt setup sMonSpriteAnchorCoords x y & placement of mon sprite on pokedex screen w constants
* based on height and mon elevation will put exact arrays here shortly 
* -do this after pokedex port

learned moves post evolution isn't propoerly showing up in summary sreen
even though I learn them its showing up blank,

the moves are in the code as learned as if I learn enough to go over 
4 it will generate add move script  its just not recognized by summaryscreen

ok and looks like learning a move (or just the weird issues with cocoon)
cause straight up game break
*
* found wrap anim end turn glitch,
* somehow roost is causing freeze again,
*furycutter isn't working again/ freezing game * but after animtion  and attack string
* some other issue with rattata as well, possibly beatup also freezing
* type reading is broken seems to be doing some form of shift when reading types
*
*
* 
* save systems and graphics for later, do smaller updates first
* file constant renames will prob have to come last as it would affect everything
* so keep base names, slowly add things in, then when everything is in I can do
* renames or just simiply copy the original files in, from main repo, instead of conversion repo
* as by then it'd be the same
*/