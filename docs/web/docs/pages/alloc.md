Syntax
------

**VOID POINTER** alloc ( &lt;**INT** size&gt; )

Description
-----------

Allocates a [block of memory](memoryblock "wikilink") of a certain size.
Returns a pointer to the newly allocating memory block, or
[NULL](NULL "wikilink") on failure.

Also called [mem\_alloc](mem_alloc "wikilink")().

Parameters
----------

  -------------- -----------------------------------------------------------------------
  **INT** size   - The size of the to be allocated memory in [bytes](byte "wikilink").
  -------------- -----------------------------------------------------------------------

Returns
-------

**VOID POINTER** : Pointer to the first element of the allocated memory
block.

  -------------------------- -------------------------------------------------------------------------------------
  [NULL](NULL "wikilink")    - There was are an error allocating the memory, like insufficient memory available.
  ![NULL](NULL "wikilink")   - Pointer to the first element of the allocated memory block.
  -------------------------- -------------------------------------------------------------------------------------

Example
-------

    import "mod_mem"
    import "mod_say"

    Process Main()
    Private
        byte* pbyte;
        word* pword;
        int* pint;
        int elements = 10;
        int i;
    Begin

        // Allocate memory
        pbyte = alloc(elements);
        pword = alloc(elements*sizeof(*pword)); // note the sizeof() here, this is possible!
        pint  = alloc(elements*sizeof(int));

        // Reset memory to 0's
        memset (pbyte,0,elements);
        memsetw(pword,0,elements); // same as  memset(pword,0,elements*sizeof(word));
                                   // because value-parameter is 0.
        memseti(pint ,0,elements); // same as  memset(pint,0,elements*sizeof(int));
                                   // because value-parameter is 0.

        // Write numbers to bytes and ints
        for(i=0; i<elements; i++)
            pbyte[i]  = 133; // pbyte[i] is the same as *(pbyte+i)
            *(pint+i) = 4555; // pint[i] is the same as *(pint+i)
        end

        // Write numbers to words
        memsetw(pword,345,elements);

        // Show numbers
        for(i=0; i<elements; i++)
            say("byte["+i+"] = " + *(pbyte+i));
            say("word["+i+"] = " + pword[i]);
            say("int ["+i+"] = " + pint[i]);
        end

    OnExit

        // Free the used memory
        free(pbyte);
        free(pword);
        free(pint);

    End

Example 2
---------

The following three examples show the difference in size, when array's
are created. Note the use of the [sizeof](sizeof "wikilink")() operator,
to calculate the amount of bytes required for the data type. You can
also allocate user defined types and even structs. Be carefull with
strings though, as they show up as 4 bytes, but in the case of strings,
you get a [pointer](pointer "wikilink") (start adress) of the
[string](string "wikilink"), wich is a 4 byte integer.

  ----------- --------------------------------------------------
  Example 1   - array of 10 (4 byte) integers
  Example 2   - array of 10 (1 byte) byte (could also be char)
  Example 3   - array of 10 (2 byte) short integers
  ----------- --------------------------------------------------

    // Some general remarks with manual memory managment, ALWAYS free data after use, and test if an
    // allocation was successfull with IF (p_test_array2==NULL). When one of these memory allocation
    // functions returns a NULL, the allocation was NOT sucessfull, and any kind of unpredicatable things
    // can happen. With manual memory managment, you'll have to really know what you're doing, as the slightest
    // mistake can cause crashes and unpredicatable behaviour, wich is one of the dangers with using pointers.



    // import modules
    IMPORT "mod_say";
    IMPORT "mod_debug";
    IMPORT "mod_mem";


     /*
        alloc(int size);
        returns: void pointer
        purpose: create a block of memory, of a certain size, the returned pointer indicates the start adress of this block.
    */




    GLOBAL

    int pointer p_first_array;    // 10 elments, created with alloc(), 10 integers       (4 byte elements)
    byte pointer p_second_array;  // 10 elments, created with alloc(), 10 bytes          (1 byte elements)
    short pointer p_third_array;  // 10 elments, created with alloc(), 10 short integers (2 byte elements)

    int elements=10;            // initial array size

    int count;                  // general purpose loop counter



    PROCESS main();

    BEGIN


       
        
        // Allocate memory (10 integers), this way we create an array of integers from (0-9, so 10 elements)
        // The alloc() function works with bytes. It is always good practice to use the sizeof() operator, because
        // you'd have to know exactly how many bytes make up a particulair data. An integer is 4 bytes in bennu,
        // so for an array of 10 elements, you need to allocate 40 bytes. If you do "alloc(elements)",like in the
        // wiki, you only get 4 bytes! so that is totally too small for you array! always use this syntax:
        // 
        // alloc(sizeof(<data_type>)), or for arrays: alloc(elements*sizeof(<data_type>)). Note that <data_type> can 
        // also be a user-defined type.
        
        p_first_array=alloc(elements*sizeof(int));
        
        // check if the allocation succeeded
        IF (p_first_array==NULL)
           // allocation failed
           say("allocation failed!! p_first_array="+p_first_array);
           
        ELSE
        
           // allocation succeeded
           // set the value's to zero
           memseti(p_first_array ,0,elements);
        
           say("");
           say("");
           // print the array
           FOR (count=0; count<elements; count+=1)
               say("p_first_array["+count+"]="+p_first_array[count]);
           END
        
           say("");
           say("");
           say("the size of the array is "+(elements*sizeof(int))+" bytes");  
           say("");
           say("");
        END
        
        
        // now let's create an array of 10 bytes, the size of the array will be 10 * 1 byte =10 bytes
        p_second_array=alloc(elements*sizeof(byte));
        
        // check if the allocation succeeded
        IF (p_first_array==NULL)
           // allocation failed
           say("allocation failed!! p_second_array="+p_second_array);
           
        ELSE
        
           // allocation succeeded
           // set the value's to zero
           memseti(p_second_array ,0,elements);
        
           say("");
           say("");
           // print the array
           FOR (count=0; count<elements; count+=1)
               say("p_second_array["+count+"]="+p_second_array[count]);
           END
        
           say("");
           say("");
           say("the size of the array is "+(elements*sizeof(byte))+" bytes");  
           say("");
           say("");
        END
        
        
        // now let's create an array of 10 short integers, the size of the array will be 10 * 2 bytes =20 bytes
        p_third_array=alloc(elements*sizeof(short));
        
        // check if the allocation succeeded
        IF (p_first_array==NULL)
           // allocation failed
           say("allocation failed!! p_second_array="+p_third_array);
           
        ELSE
        
           // allocation succeeded
           // set the value's to zero
           memseti(p_third_array ,0,elements);
        
           say("");
           say("");
           // print the array
           FOR (count=0; count<elements; count+=1)
               say("p_third_array["+count+"]="+p_third_array[count]);
           END
        
           say("");
           say("");
           say("the size of the array is "+(elements*sizeof(short))+" bytes");  
           say("");
           say("");
        END    
        

        


     
        
    ONEXIT

       // Free the used memory
       say("freeing old memory........");
       say("p_first_array...");
       free(p_first_array);
       say("ok");
       
       say("freeing old memory........");
       say("p_second_array...");
       free(p_second_array);
       say("ok");
       
       say("freeing old memory........");
       say("p_third_array...");
       free(p_third_array);
       say("ok");
    END

Used in example: [alloc](alloc "wikilink")(),
[memset](memset "wikilink")(), [memsetw](memsetw "wikilink")(),
[memseti](memseti "wikilink")(), [sizeof](sizeof "wikilink")(),
[say](say "wikilink")(), [free](free "wikilink")(),
[OnExit](OnExit "wikilink"), [pointer](pointer "wikilink"),
[sizeof](sizeof "wikilink")

<Category:functions> <Category:memory> <Category:mod_mem>
