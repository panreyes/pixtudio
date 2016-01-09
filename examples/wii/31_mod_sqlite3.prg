/*
  SQLite3 Bennu Interface
  Small. Fast. Reliable

  SQLite is a in-process library that implements a self-contained,
  serverless, zero-configuration, transactional SQL database engine.
  The code for SQLite is in the public domain and is thus free for use
  for any purpose, commercial or private. SQLite is currently found in
  more applications than we can count, including several high-profile projects.


  http://www.sqlite.org/

*/

import "mod_video"
import "mod_key"
import "mod_mouse"
import "mod_rand"
import "mod_sqlite3"
import "mod_text"

GLOBAL
    res,db,i;
    filepath="sd:/APPS/examples/score.db";
    SqlResult sqlRes;  // It's an Struct
    string fieldname[20];
    string fieldvalue[20];
    mover=true;
    string CreateScore= "CREATE TABLE tablescore ("
        "idgen INTEGER  PRIMARY KEY NOT NULL,"
        "name VARCHAR(40) NOT NULL,"
	    "score INTEGER ,"
	    "level INTEGER, "
	    "enterd DATE DEFAULT (DATETIME('NOW'))"
        "); ";
    scr_width = 640, scr_height=480;
end

Process main()
BEGIN
    // Check that we can set the video mode before actually setting it
    if(!mode_is_ok(scr_width, scr_height, 16, MODE_WINDOW))
        return -1;
    end;
    set_mode(scr_width, scr_height, 16, MODE_WINDOW);

    db= sqlite3_open(filepath,SQLITE_OPEN_READWRITE  | SQLITE_OPEN_CREATE); //create if not exist

    if (db)
        write(0,100,110,0,"Database open correctly.." );
        if (SQLITE3_EXEC(db,CreateScore)<>SQLITE_OK)  //create example tables
            write(0,100,120,0,"SQL error: "+SQLITE3_ERRMSG(db) ); //example error
	    end
	    SQLITE3_EXEC(db,"BEGIN TRANSACTION");
	    for (i=1;i<20;i++)
		    res = SQLITE3_EXEC(db,"INSERT INTO tablescore(name,score,level) VALUES"
	            "('player"+i+"',"+     //name
				rand(20,2000)+","+      //score
			    rand(1,15)+  //level
				")");
	        if (res<>SQLITE_OK) break; end //error?
	    end

        if ( res==SQLITE_OK )
            SQLITE3_EXEC(db,"COMMIT");
	    else
	        SQLITE3_EXEC(db,"ROLLBACK");
        end

        write(0,100,130,0,"Records Affected : "+SQLITE3_TOTALCHANGES(db) ); //print total number of records affected

	    //list the best 10 players
        SQLITE3_OPENTABLE(db,"SELECT * FROM tablescore ORDER BY score DESC,enterd DESC LIMIT 10",SqlRes); //get rows with OPENTABLE	(only read)

        if (SqlRes.rows <= 0)
            write(0,100,150,0,"Not records found");
        	if (1 <= 0)
        	    write(0,100,150,0,"Not records found");
		    else
		        write(0,100,150,0,"Press left and right to navigate..");
		        write(0,100,160,0,"Records Found in Select: "+SqlRes.rows);
		    end;
        else
            write(0,100,100,0,"Open Error  ..." );
        end;

        while (! mouse.left)
            if (key(_left) )
                if (SqlRes.CurrentRow>1)
                    SqlRes.CurrentRow--;
	                mover=true;
                end;
	        end;

            if (key(_right) )
                if (SqlRes.CurrentRow < SqlRes.rows)
                    SqlRes.CurrentRow++;
                    mover=true;
                end;
            end;

            if (SqlRes.rows > 0 and db and mover) //exist records?
                for (x=0;x<SqlRes.cols;x++)
                    Fieldname[x]= SQLITE3_GETFIELDNAME(SqlRes,x);	//get field name
                    write_string(0,10,200+(10*x),0,&fieldname[x]);
                    fieldvalue[x]= SQLITE3_GETFIELDVALUE(SqlRes,x);  //get field value
                    write_string(0,100,200+(10*x),0,&fieldvalue[x]);
                end;
                mover=false;
                while (key(_right) or key(_left) )
                    frame;
                end; //clean keyboard buffer to navigate slow
	        end;

      	    frame;
        end

        SQLITE3_CLOSETABLE(SqlRes);
        SQLITE3_CLOSE(db);
    end
end
