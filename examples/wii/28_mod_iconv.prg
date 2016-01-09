import "mod_say";
import "mod_file";
import "mod_iconv";

Process main()
Private
	string fname="cancion.txt", line="";
	int fd=0;

Begin
	say("Going to read file "+fname);
	/* It's really José de Espronceda */
	/* http://es.wikipedia.org/wiki/José_de_Espronceda */
	say("This poem was written by the famous spanish poet Jose de Espronceda.");
	say("");
	fd = fopen(fname, O_READ);
	if(fd == 0)
	    say("Couldn't load poem file :(");
	else
	    while(!feof(fd))
	    	line = fgets(fd);
	    	say(iconv("UTF8", "ISO-8859-15//TRANSLIT", line));
	    end;
	    fclose(fd);
	end;
End;
