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
* .type chart -						done
* 4.species names update -			done
* 5.base stats
* 6.friendship rework -				done (missing base stats changes)
* 7.ability constant ability data 
* 8.move info data file and move constants 
* .summary screen ui
* .battle ui
* .name expansion -					partial
* pokedex ui.
* removal of lg pokedex entries.
* emerald stye naming screen. for intro, add fade in for rival rename
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