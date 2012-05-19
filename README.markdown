Asgaard Technologies Aera (Open Source Version)
===============================================


Prerequirements
------------------------------

- cmake
- qt
- libqxt


Installation
-----------------------------

    cmake ..
    make
    make install


The workingset
------------------------------

Aera is a collection of various executables in three main categories.

-   Input: read various formats into xml.
-   Output: transform xml to various taget media.
-   Transform: read an xml stream and output an xml stream filtered/trasnformed.

Those tools are connected with pipes. they all use the same format: xml.


Input
------------------------------

For example for reading an csv file into a format we can work with, that beeing xml, we can use csv2xml:

    ~$ echo -e "A;B;C;D;E;F\nThis;is;some;sort;of;CSV\n" | csv2xml -d ';'
    <csv>
        <row>
            <A>This</A>
            <B>is</B>
            <C>some</C>
            <D>sort</D>
            <E>of</E>
            <F>CSV</F>
        </row>
    </csv>


Output
--------------------------------

Of course we could output the data we gathered above, directly into csv again.
Or make up some of our own. What is important,
is that most output targets require the xml stream to be in a certain format.
Thats becouse the format it is supposed to write, is often limited.

For example this does not actually work:

            ~$  echo " <A><B><C><D></D></C></B></A> |  xml2csv


since csv is limited to a depth of 3. that beeing: file>row>column
This data stream works fine

            ~$  echo " <csv><row><A>Hello</A><B>World</B></row></csv>|  xml2csv -d ';'
            A;B
            Hello;World

Note that the name of the first two nodes (csv and row) is ignored anyway,
since csv has no way of storing them. they are purely structural information.


Transformation
--------------------------------------

For trasnformation xml data, the most common two techniques are xslt and xquery.
So far we support xquery via gcx and patternist.
GCX is the right choice for high performance applications, or infinite streams.
Patternist is more complete in its xquery support, but technicaly weaker,
and it will fail horribly at infinite data pipes.

    ~$ echo  -r "A;B\nHello;World\n"  csv2xml | gcx -e "{for  i in ./csv/row/A return <X>{$i}</X>}"
    <X>Hello</X>


Vengenace
----------------------------------------

Vengeance is a beast that's hard to handle.
But it's worth it. It allows importing data into sql databases using xml.

### Object Structure

To import a single object, you'd have to structure your xml like this:

    <customers>
        <customer   id="976"  name="Hans"  />
    </customers>

Vengeance will automaticly convert singular to plural,
and expect the table name to be plural. In this case the SQL table would look like:

    customers:
       varchar  id
       varchar  name

### Qualification

When defining a table in sql, you give the table key and unique fields.
These fields are used to qualify a row. Keys have to be either defined in your xml stream,
or be set to auto increment in your sql database.
Vengeance will first of all try to match your object with an existing Object in the database,
using keys, uniques, or relations to parent and child objects.
If it cannot find a match, it will attemp to insert a new object into the database.
If it cannot find enough information to create a unique object, it will throw an error.

### Relations

When importing Objects into a relational database, you can use the structure of the xml stream
to define the relation between objects

    <customers>
        <customer   id="976" >
            <order value="23" >
        </customer>
    </customers>

The relation between the table "customers" and "orders" will be automaticly detected by qualification keys.
Vengeance assumes that fields forming the relation have the same name in both tables.
