Syntax
------

**INT POINTER** crypt\_new ( &lt;**INT** method&gt; , &lt;**CHAR
POINTER** key&gt;)

Description
-----------

Create a handle to start to encrypt information.

Parameters
----------

  ---------------------- -------------------------------------------------------
  **INT** method         - Method to encrypt. may be CRYPT\_DES or CRYPT\_3DES
  **CHAR POINTER** key   - key used to the encryption.
  ---------------------- -------------------------------------------------------

Returns
-------

**INT POINTER** : crypt handle identifier. It is 0 then the handle can
not be created.

<Category:functions> <Category:crypt> <Category:mod_crypt>