Syntax
------

**VOID POINTER** realloc ( &lt;**VOID POINTER** data&gt; , &lt;**INT**
size&gt; )

Description
-----------

Resizes the given block of memory.

It allocates a new block of memory, copying the old data. If the new
size is smaller than the old size, the last part of the data is lost. If
the new size of the block of memory requires movement of the block, the
old memory block is freed.

Also called [mem\_realloc](mem_realloc "wikilink")().

Parameters
----------

  ----------------------- -------------------------------------------------
  **VOID POINTER** data   - Pointer to the block of memory to be resized.
  **INT** size            - The new size of the block of memory in bytes.
  ----------------------- -------------------------------------------------

Returns
-------

**VOID POINTER** : Pointer to (the first element of) the newly allocated
memory block.

  -------------------------- -------------------------------------------------------------------------------------
  [NULL](NULL "wikilink")    - There was are an error allocating the memory, like insufficient memory available.
  ![NULL](NULL "wikilink")   - Pointer to (the first element of) the newly allocated memory block.
  -------------------------- -------------------------------------------------------------------------------------

Example
-------

    import "mod_mem"
    import "mod_say"

    Process Main()
    Private
        byte pointer pbyte;
        byte pointer pbyte2;
        int elements = 10;
        int newelements = 15;
        int i;
    Begin

        // Allocate memory
        pbyte = alloc(elements);

        // Set them to 13
        memset(pbyte,13,elements);

        // Relocate it to a larger, newly made memory block
        pbyte2 = realloc(pbyte,newelements);

        // Set the added part's elements to 16 (newelements > elements)
        memset(pbyte+elements,16,newelements-elements);

        // Show numbers
        for(i=0; i<newelements; i++)
            say("byte2["+i+"] = " + pbyte2[i]);
        end

    OnExit

        // Free the used memory
        free(pbyte2);

    End

Example 2
---------


    // Alloc, calloc and realloc tutorial, by handsource-dyko.

    // This sample program demonstrates how create integer array's with alloc, and calloc, 
    // and how to resize them with realloc. 

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

    /*
        calloc(int size,type);
        returns: void pointer
        purpose: create a block of memory, of a certain size, the returned pointer indicates the start adress of this block.
                 is used for creating arrays.
    */
        
    /*

       realloc (void pointer data, int size);
       returns: void pointer
       purpose: resizes the given block of memory, it allocates a new block of memory, copying the old data. 
                if the new size is smaller than the old size, the last part of the data is lost. 
                if the new size of the block of memory requires movement of the block, the old memory block is freed. 

    */


    GLOBAL

    int pointer p_first_array;  // 10 elments, created with alloc()
    int pointer p_third_array;  // 10 elments, created with calloc()
    int pointer p_second_array; // resized copy of p_first_array, 15 elements, created with realloc()
    int pointer p_fourth_array; // resized copy of p_second_array, 15 elements, created with realloc()


    int test[9];                // simple array with 10 elements
    int pointer p_test_array;   // will be used for storing the pointer to test[0]
    int pointer p_test_array2;  // will be the resized array, created with realloc, is now 15 elements

    int elements=10;            // initial array size
    int new_elements=15;        // new array size

    int count;                  // general purpose loop counter



    PROCESS main();

    BEGIN


        // standard array
        say("");
        say("");
        // print the array
        FOR (count=0; count<elements; count+=1)
            say("test["+count+"]="+test[count]);
        END
        
        say("");
        say("");
        say("the size of the array 'test' is "+sizeof(test)+" bytes");  
        say("");
        say("");
      
        

       
        
        // Allocate memory (10 integers), this way we create an array of integers from (0-9, so 10 elements)
        // The alloc() function works with bytes. It is always good practice to use the sizeof() operator, because
        // you'd have to know exactly how many bytes make up a particulair data. An integer is 4 bytes in bennu,
        // so for an array of 10 elements, you need to allocate 40 bytes. If you do "alloc(elements)",like in the
        // wiki, you only get 10 bytes! so that is totally too small for you array! always use this syntax:
        // 
        // alloc(sizeof(<data_type>)), or for arrays: alloc(elements*sizeof(<data_type>)). Note that <data_type> can 
        // also be a user-defined type.
        
        p_first_array=alloc(elements*sizeof(int));
        //p_first_array=calloc(elements,sizeof(int));
        
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
        

        

        
        // Now let's use calloc to create the same array, but calloc is a bit smarter. It's more suited to array's and
        // it even initializes all the data to 0 for you, so that you can omit the memset() function. In this case I 
        // kept memseti() in there, but you can omit it when using calloc(). But with alloc() you need to use it!
        
        // Note the small difference between alloc() and calloc().
        
        //p_second_array=alloc(elements*sizeof(int));
        p_second_array=calloc(elements,sizeof(int));
        
        
        // check if the allocation succeeded
        IF (p_second_array==NULL)
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
           say("the size of the array is "+(elements*sizeof(int))+" bytes");
           say("");
           say("");
        END   
        

        
        
        // Let's resize p_first_array to a bigger size (15). This is where realloc() is used for. Also, just as with
        // alloc(), it is important to remember that it works with bytes! So we use this (new_elements*sizeof(int)) again.
        p_third_array=realloc(p_first_array,(new_elements*sizeof(int)));
        
        // check if the allocation succeeded
        IF (p_third_array==NULL)
           // allocation failed
           say("allocation failed!! p_third_array="+p_third_array);
           
        ELSE
        
           // allocation succeeded
           // set the value's to zero
           memseti(p_third_array ,0,new_elements);
           
       
           say("");
           say("");
           // print the array
           FOR (count=0; count<new_elements; count+=1)
               say("p_third_array["+count+"]="+p_third_array[count]);
           END
        
           say("");
           say("");
           say("the size of the array is "+(new_elements*sizeof(int))+" bytes");  
           say("");
           say("");
        END
      
        
       
        // Let's resize p_second_array to a bigger size (15).
        p_fourth_array=realloc(p_second_array,(new_elements*sizeof(int)));
      
        
        // check if the allocation succeeded
        IF (p_fourth_array==NULL)
           // allocation failed
           say("allocation failed!! p_fourth_array="+p_fourth_array);
           
        ELSE
        
           // allocation succeeded
           // set the value's to zero
           memseti(p_fourth_array ,0,new_elements);
           
           say("");
           say("");
           
           // print the array
           
           FOR (count=0; count<new_elements; count+=1)
               say("p_fourth_array["+count+"]="+p_fourth_array[count]);
           END
           
           say("");
           say("the size of the array is "+(new_elements*sizeof(int))+" bytes");  
           say("");
           say("");
        END
     

        // Let's try to resize an standard array (the array test[9]) to 15 
        p_test_array=test[0];   // <-- p_test_array is a pointer, we store the ADRESS of the first element (wich is 0) in it.
                                // test[0] is actually a pointer itself, it represents the start adress of the array.
                                // The whole concept of array indexing is actuallty a concealed form of pointer artihmatic,
                                // consult any good C book about the details of this. 
        p_test_array2=realloc(p_test_array,(new_elements*sizeof(int)));
      
        
        // check if the allocation succeeded
        IF (p_test_array2==NULL)
           // allocation failed
           say("allocation failed!! p_test_array2="+p_test_array2);
           
        ELSE
        
           // allocation succeeded
           // set the value's to zero
           memseti(p_test_array2 ,0,new_elements);
           
           say("");
           say("");
           
           // print the array
           
           FOR (count=0; count<new_elements; count+=1)
               say("p_test_array2["+count+"]="+p_test_array2[count]);
           END
           
           say("");
           say("the size of the array is "+(new_elements*sizeof(int))+" bytes");  
           say("");
           say("");
        END


     
        
    ONEXIT

       // Free the used memory
       say("freeing old memory........");
       say("p_first_array...");
       free(p_first_array);
       say("ok");
       say("p_second_array...");
       free(p_second_array);
       say("ok"); 
       say("p_third_array...");
       free(p_third_array);
       say("ok");
       say("p_fourth_array...");
       free(p_fourth_array);
       say("ok");  
       say("p_test_array...");
       free(p_test_array);
       say("ok"); 
       say("p_test_array2...");
       free(p_test_array2);
       say("ok");
       
    END

Used in example: [alloc](alloc "wikilink")(),
[memset](memset "wikilink")(), [realloc](realloc "wikilink")(),
[say](say "wikilink")(), [free](free "wikilink")(),
[pointer](pointer "wikilink")

<Category:functions> <Category:memory> <Category:mod_mem>
