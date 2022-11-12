# LoginSQL
An SQL User Login System, using QT and C++.

Allowing access to a platform only to selected users is a common procedure and so here is an example of how to achieve it with QT, C++ and SQL. You will initially have your bonafide users set up on an SQL Database and then your program will initially connect to it and be able to query it any time new log on information is provided.

If no matching log on information is found from the Database Query the user is informed through the statusbar that an error has occurred and to try again. Otherwise it grants them access to the next Phase of the platform. In this case I am just showing them personal information stored in the database about them.

Add as many users as you like to the SQL Database and they will all be granted access.

https://user-images.githubusercontent.com/111576658/201483030-1d8224f7-4d38-4d54-8044-bb1cdff6b41e.mp4

