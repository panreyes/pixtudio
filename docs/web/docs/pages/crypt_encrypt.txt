Syntax
------

*' INT*' crypt\_encrypt ( &lt;**INT POINTER** handle&gt;, &lt;**CHAR
POINTER** in&gt;, &lt;**CHAR POINTER** out&gt;, &lt;**INT** blocks&gt;,
)

OR

*' INT*' crypt\_encrypt ( &lt;*' INT*' method&gt;, &lt;**CHAR POINTER**
key&gt;, &lt;**CHAR POINTER** in&gt;, &lt;**CHAR POINTER** out&gt;,
&lt;**INT** blocks&gt;, )

Description
-----------

Encrypt a selected data using a handle or creating a handle with the
given method and key.

Parameters
----------

  ------------------------ -------------------------------------------------------
  **INT** method           - Method to encrypt. may be CRYPT\_DES or CRYPT\_3DES
  **CHAR POINTER** key     - key used to the encryption.
  **INT POINTER** handle   - handle to use to encrypt.
  **CHAR POINTER** in      - data to encrypt.
  **CHAR POINTER** out     - pointer for where to write encrypted data.
  **INT** blocks           - length of the data to encrypt.
  ------------------------ -------------------------------------------------------

Returns
-------

**INT** : Successrate

  ---- ----------
  -1   - Error.
  0    - Ok.
  ---- ----------

<Category:functions> <Category:crypt> <Category:mod_crypt>
