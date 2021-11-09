import java.io.IOException;
import java.sql.*;

public class Main {
    public static void main(String[] args) throws Exception {

        try {
            Class.forName("org.postgresql.Driver");
        } catch (ClassNotFoundException e) {
            System.out.println("Where is your PostgreSQL JDBC Driver? Include in your library path!");
            e.printStackTrace();
            return;
        }
        System.out.println("PostgreSQL JDBC Driver Registered!");
        /// if you have a error in this part, check jdbc driver(.jar file)

        Connection connection = null;

        try {
            connection = DriverManager.getConnection(
                    "jdbc:postgresql://127.0.0.1:5432/project_movie", "postgres", "cse3207");
        } catch (SQLException e) {
            System.out.println("Connection Failed! Check output console");
            e.printStackTrace();
            return;
        }
        /// if you have a error in this part, check DB information (db_name, user name, password)

        if (connection != null) {
            System.out.println(connection);
            System.out.println("You made it, take control your database now!");
        } else {
            System.out.println("Failed to make connection!");
        }


        /////////////////////////////////////////////////////
        ////////// write your code on this ////////////
        /////////////////////////////////////////////////////
        //initial data
        try {
        	
        	Statement stmt = connection.createStatement();
        	
			String sql = "create table "+ "director"
						+ "("
						+ " directorID serial , "
						+ "directorName varchar(20), "
						+ "dateOfBirth char(10), "
						+ "dateOfDeath char(10), "
						+ " PRIMARY KEY (directorID) "
						+ ")";

			stmt.executeUpdate(sql);
			sql = "create table "+ "actor"
						+ "("
						+ "actorID serial, "
						+ "actorName varchar(20), "
						+ "dateOfBirth varchar(20), "
						+ "dateOfDeath varchar(20), "
						+"gender varchar(6),"
						+ "PRIMARY KEY (actorID) "

						+ ")";	
			stmt.executeUpdate(sql);
			sql = "create table "+ "movie"
						+ "("
						+ "movieID serial, "
						+ "movieName varchar(50), "
						+ "releaseYear varchar(10), "
						+ "releaseMonth varchar(10), "
						+ "releaseDate varchar(20), "
						+" publisherName varchar(50),"
						+" avgRate	numeric(8, 2) default 0.00,"
						+ "PRIMARY KEY (movieID) "
						+ ")";	
			stmt.executeUpdate(sql);

			sql = "create table "+ "award"
						+ "("
						+ "awardID serial, "
						+ "awardName varchar(50), "
						+ "PRIMARY KEY (awardID) "
						+ ")";	
			stmt.executeUpdate(sql);

			sql = "create table "+ "genre"
						+ "("
						+ "genreName varchar(20), "
						+ "PRIMARY KEY (genreName) "
						+ ")";	
			stmt.executeUpdate(sql);

			sql = "create table "+ "movieGenre"
						+ "("
						+ "movieID integer, "
						+ "genreName char(50), "
						+"foreign key (movieID) references movie on delete cascade,"
						+"foreign key (genreName) references genre on delete cascade,"
						+ "PRIMARY KEY (movieID,genreName) "

						+ ")";	
			stmt.executeUpdate(sql);

			sql = "create table "+ "movieObtain"
						+ "("
						+ "movieID integer, "
						+ "awardID integer, "
						+ " year varchar(20), "
						+"foreign key (movieID) references movie on delete cascade,"
						+"foreign key (awardID) references award on delete cascade,"
						+ "PRIMARY KEY (movieID,awardID) "
						+ ")";	
			stmt.executeUpdate(sql);
			 sql = "create table "+ "actorObtain"
						+ "("
						+ "actorID integer ,"
						+ "awardID integer,"
						+ " year varchar(20), "
						+ "PRIMARY KEY (actorID,awardID), "
						+ "foreign key (awardID) references award on delete cascade,"
						+ "foreign key (actorID) references actor on delete cascade"
						+ ")";	
			stmt.executeUpdate(sql);

			sql = "create table "+ "directorObtain"
						+ "("
						+ "directorID integer,"
						+ "awardID integer,"
						+ " year varchar(20), "
						+ "PRIMARY KEY (directorID,awardID) ,"
						+ "foreign key (awardID) references award on delete cascade,"
						+ "foreign key (directorID) references director on delete cascade"
						+ ")";	
			stmt.executeUpdate(sql);
			

			 sql = "create table "+ "casting"
						+ "("
						+ "movieID integer,"
						+ "actorID integer,"
						+ "role varchar(20), "
						+ "PRIMARY KEY (movieID,actorID), "
						+ "foreign key (movieID) references movie on delete cascade,"
						+ "foreign key (actorID) references actor on delete cascade"
						+ ")";	
			stmt.executeUpdate(sql);

			 sql = "create table "+ "make"
						+ "("
						+ "movieID integer, "
						+ "directorID integer,"
						+ "PRIMARY KEY (movieID,directorID), "
						+ "foreign key (movieID) references movie on delete cascade,"
						+ "foreign key (directorID) references director on delete cascade"
						+ ")";	
			stmt.executeUpdate(sql);

			sql = "create table "+ "customerRate"
						+ "("
						+ "customerID integer,"
						+ "movieID integer,"
						+ "rate char(20), "
						+ "PRIMARY KEY (customerID,movieID) "
						+ ")";	
			stmt.executeUpdate(sql);
			sql = "create table "+ "customer"
						+ "("
						+ "customerID serial,"
						+ "customerName char(20), "
						+ "dateOfBirth char(20), "
						+ "gender char(20), "
						+ "PRIMARY KEY (customerID) "
						+ ")";	
			stmt.executeUpdate(sql);
			stmt.close();
            System.out.println("Table created!");


            }			
			 catch (SQLException e) {
		        	e.printStackTrace();
		        }
        try {
        	Statement stmt = connection.createStatement();

        	String sql = "insert into movie (movieName,releaseDate,publisherName)VALUES ('Edward Scissorhands','1991.06.29','20th Century Fox Presents')";
        	stmt.executeUpdate(sql);
        	sql = "insert into movie (movieName,releaseDate,publisherName)VALUES ('Alice In Wonderland','2010.03.04','Korea Sony Pictures')";
        	stmt.executeUpdate(sql);
        	sql = "insert into movie (movieName,releaseDate,publisherName)VALUES ('The Social Network','2010.11.18','Korea Sony Pictures')";
        	stmt.executeUpdate(sql);
        	sql = "insert into movie (movieName,releaseDate,publisherName)VALUES ('The Dark Knight','2008.08.06','Warner Brothers Korea')";
        	stmt.executeUpdate(sql);
        	sql = "insert into movie (movieName,releaseDate,publisherName)VALUES ('Dunkirk','2017.07.13','Warner Brothers Korea')";
        	stmt.executeUpdate(sql);
        	
        	 sql = "insert into director (directorName,dateOfBirth)VALUES ('Tim Burton','1958.8.25')";
        	stmt.executeUpdate(sql);
       	 	sql = "insert into director (directorName,dateOfBirth)VALUES ('David Fincher','1962.8.28')";
       	 	stmt.executeUpdate(sql);
       	 	sql = "insert into director (directorName,dateOfBirth)VALUES ('Christopher Nolan','1970.7.30')";
       	 	stmt.executeUpdate(sql);
       	 	
       	 	sql = "insert into actor (actorName,dateOfBirth,gender)VALUES ('Tim Burton','1963.6.9','Male')";
       	 	stmt.executeUpdate(sql);
    	 	sql = "insert into actor (actorName,dateOfBirth,gender)VALUES ('Winona Ryder','1971.10.29','Female')";
       	 	stmt.executeUpdate(sql);
    	 	sql = "insert into actor (actorName,dateOfBirth,gender)VALUES ('Mia Wasikowska','1989.10.14','Female')";
       	 	stmt.executeUpdate(sql);
    	 	sql = "insert into actor (actorName,dateOfBirth,gender)VALUES ('Christian Bale','1974.1.30','Male')";
       	 	stmt.executeUpdate(sql);
    	 	sql = "insert into actor (actorName,dateOfBirth,dateofdeath,gender)VALUES ('Heath Ledger','1979.4.4','2008.1.22','Male')";
       	 	stmt.executeUpdate(sql);
    	 	sql = "insert into actor (actorName,dateOfBirth,gender)VALUES ('Jesse Eisenberg','1983.10.5','Male')";
       	 	stmt.executeUpdate(sql);
    	 	sql = "insert into actor (actorName,dateOfBirth,gender)VALUES ('Justin Timberlake','1981.1.31','Male')";
       	 	stmt.executeUpdate(sql);
    	 	sql = "insert into actor (actorName,dateOfBirth,gender)VALUES ('Fionn Whitehead','1997.7.18','Male')";
       	 	stmt.executeUpdate(sql);
    	 	sql = "insert into actor (actorName,dateOfBirth,gender)VALUES ('Tom Hardy','1977.9.15','Male')";
       	 	stmt.executeUpdate(sql);
       	 	
       	 	
       	
       	 	sql = "insert into genre (genreName)VALUES ('Fantasy')";
       	 	stmt.executeUpdate(sql);
       	 	sql = "insert into genre (genreName)VALUES ('Romance')";
       	 	stmt.executeUpdate(sql);
       	 	sql = "insert into genre (genreName)VALUES ('Adventure')";
       	 	stmt.executeUpdate(sql);
       		sql = "insert into genre (genreName)VALUES ('Drama')";
       	 	stmt.executeUpdate(sql);
       	 	sql = "insert into genre (genreName)VALUES ('Action')";
    	 	stmt.executeUpdate(sql);
    	 	sql = "insert into genre (genreName)VALUES ('Mystery')";
    	 	stmt.executeUpdate(sql);
    	 	sql = "insert into genre (genreName)VALUES ('Thriller')";
       	 	stmt.executeUpdate(sql);
       	 	sql = "insert into genre (genreName)VALUES ('Family')";
    	 	stmt.executeUpdate(sql);
    	 	sql = "insert into genre (genreName)VALUES ('War')";
    	 	stmt.executeUpdate(sql);
    	 	
    	 	sql = "insert into moviegenre (movieID,genreName)VALUES ('1','Fantasy')";
    	 	stmt.executeUpdate(sql);
    		sql = "insert into moviegenre (movieID,genreName)VALUES ('1','Romance')";
    	 	stmt.executeUpdate(sql);
    		sql = "insert into moviegenre (movieID,genreName)VALUES ('2','Fantasy')";
    	 	stmt.executeUpdate(sql);
    	 	sql = "insert into moviegenre (movieID,genreName)VALUES ('2','Adventure')";
    	 	stmt.executeUpdate(sql);
    	 	sql = "insert into moviegenre (movieID,genreName)VALUES ('2','Family')";
    	 	stmt.executeUpdate(sql);
    		sql = "insert into moviegenre (movieID,genreName)VALUES ('3','Drama')";
    	 	stmt.executeUpdate(sql);
    		sql = "insert into moviegenre (movieID,genreName)VALUES ('4','Action')";
    	 	stmt.executeUpdate(sql);
    	 	sql = "insert into moviegenre (movieID,genreName)VALUES ('4','Drama')";
    	 	stmt.executeUpdate(sql);
    	 	sql = "insert into moviegenre (movieID,genreName)VALUES ('4','Mystery')";
    	 	stmt.executeUpdate(sql);
    	 	sql = "insert into moviegenre (movieID,genreName)VALUES ('4','Thriller')";
    	 	stmt.executeUpdate(sql);
    		sql = "insert into moviegenre (movieID,genreName)VALUES ('5','Action')";
    	 	stmt.executeUpdate(sql);
    		sql = "insert into moviegenre (movieID,genreName)VALUES ('5','Drama')";
    	 	stmt.executeUpdate(sql);
    		sql = "insert into moviegenre (movieID,genreName)VALUES ('5','Thriller')";
    	 	stmt.executeUpdate(sql);
    		sql = "insert into moviegenre (movieID,genreName)VALUES ('5','War')";
    	 	stmt.executeUpdate(sql);
    	 	
    	 	sql = "insert into casting (movieId,actorId,role)VALUES ('1','1','Main actor')" ;
       	 	stmt.executeUpdate(sql);
       	 	sql = "insert into casting (movieId,actorId,role)VALUES ('1','2','Main actor')" ;
       	 	stmt.executeUpdate(sql);
       	 	sql = "insert into casting (movieId,actorId,role)VALUES ('2','1','Main actor')" ;
       	 	stmt.executeUpdate(sql);
       	 	sql = "insert into casting (movieId,actorId,role)VALUES ('2','3','Main actor')" ;
       	 	stmt.executeUpdate(sql);
       	 	sql = "insert into casting (movieId,actorId,role)VALUES ('3','6','Main actor')" ;
       	 	stmt.executeUpdate(sql);
       	 	sql = "insert into casting (movieId,actorId,role)VALUES ('3','7','Supporting Actor')" ;
       	 	stmt.executeUpdate(sql);
       	 	sql = "insert into casting (movieId,actorId,role)VALUES ('4','4','Main actor')" ;
       	 	stmt.executeUpdate(sql);
       	 	sql = "insert into casting (movieId,actorId,role)VALUES ('4','5','Main actor')" ;
       	 	stmt.executeUpdate(sql);
       	 	sql = "insert into casting (movieId,actorId,role)VALUES ('5','8','Main actor')" ;
       	 	stmt.executeUpdate(sql);
       	 	sql = "insert into casting (movieId,actorId,role)VALUES ('5','9','Supporting Actor')" ;
       	 	stmt.executeUpdate(sql);
       	 	
       		sql = "insert into make (movieId,directorID)VALUES ('1','1')" ;
       	 	stmt.executeUpdate(sql);
       		sql = "insert into make (movieId,directorID)VALUES ('2','1')" ;
       	 	stmt.executeUpdate(sql);
       		sql = "insert into make (movieId,directorID)VALUES ('3','2')" ;
       	 	stmt.executeUpdate(sql);
       		sql = "insert into make (movieId,directorID)VALUES ('4','3')" ;
       	 	stmt.executeUpdate(sql);
       		sql = "insert into make (movieId,directorID)VALUES ('5','3')" ;
       	 	stmt.executeUpdate(sql);
       	 	
       		sql = "insert into customer (customerName,dateOfBirth,gender)VALUES ('Ethan','1997.11.14','Male')" ;
       	 	stmt.executeUpdate(sql);
    		sql = "insert into customer (customerName,dateOfBirth,gender)VALUES ('John','1978.01.23','Male')" ;
       	 	stmt.executeUpdate(sql);
    		sql = "insert into customer (customerName,dateOfBirth,gender)VALUES ('Hayden','1980.05.04','Female')" ;
       	 	stmt.executeUpdate(sql);
    		sql = "insert into customer (customerName,dateOfBirth,gender)VALUES ('Jill','1981.04.17','Female')" ;
       	 	stmt.executeUpdate(sql);
    		sql = "insert into customer (customerName,dateOfBirth,gender)VALUES ('Bell','1990.05.14','Female')" ;
       	 	stmt.executeUpdate(sql);
        	stmt.close();
            System.out.println("Initial data inserted!");

        } catch (SQLException e) {
        	e.printStackTrace();
        }
        
        
        
        //insert
        try {
		    Statement stmt = connection.createStatement();
		    ResultSet rs;
        	String sql ="insert into award (awardName)VALUES('Best supporting actor')";
        	stmt.executeUpdate(sql);
        	sql = "insert into actorObtain(actorID,awardID,year)VALUES('2','1','1994')";
        	stmt.executeUpdate(sql);
        	
            System.out.println(String.format("============================================================="));
            System.out.println("Statement : 2.1. Winona Ryder won the ��Best supporting actor�� award in 1994");
            System.out.println("TranslatedSQL : insert into award (awardName)VALUES('Best supporting actor')");
            System.out.println("TranslatedSQL : insert into actorObtain(actorID,awardID,year)VALUES('2','1','1994')");
            System.out.println("-----<award>-----");
            System.out.println(String.format("%-10s|%-10s", "awardID", "awardName"));
            rs=stmt.executeQuery("select * from award");
            while(rs.next()) {
            System.out.println(String.format("%-10s|%-10s", rs.getString(1), rs.getString(2)));
            }
            System.out.println("-----<actorObtain>-----");
            rs=stmt.executeQuery("select * from actorObtain");
            System.out.println(String.format("%-10s|%-10s|%-10s", "actorID", "awardID","year"));
            while(rs.next()) {
                System.out.println(String.format("%-10s|%-10s|%-10s", rs.getString(1), rs.getString(2),rs.getString(3)));
                }
            System.out.println(String.format("============================================================="));

            
            
            sql = "insert into actorObtain(actorID,awardID,year)VALUES('9','1','2018')";
        	stmt.executeUpdate(sql);
            System.out.println(String.format("============================================================="));
            System.out.println("Statement : 2.2. Tom Hardy won the ��Best supporting actor�� award in 2018");
            System.out.println("TranslatedSQL : insert into actorObtain(actorID,awardID,year)VALUES('9','1','2018')");
            System.out.println("-----<actorObtain>-----");
            rs=stmt.executeQuery("select * from actorObtain");
            System.out.println(String.format("%-10s|%-10s|%-10s", "actorID", "awardID","year"));
            while(rs.next()) {
                System.out.println(String.format("%-10s|%-10s|%-10s", rs.getString(1), rs.getString(2),rs.getString(3)));
                }
            System.out.println(String.format("============================================================="));
            
        	

        	sql ="insert into award (awardName)VALUES('Best villain actor')";
        	stmt.executeUpdate(sql);
        	sql = "insert into actorObtain(actorID,awardID,year)VALUES('5','2','2009')";
        	stmt.executeUpdate(sql);
            System.out.println(String.format("============================================================="));
             System.out.println("Statement :2.3. Heath Ledger won the ��Best villain actor�� award in 2009");
             System.out.println("TranslatedSQL : insert into actorObtain(actorID,awardID,year)VALUES('5','2','2009')");
             System.out.println("TranslatedSQL : insert into award (awardName)VALUES('Best villain actor')");
             System.out.println("-----<award>-----");
             System.out.println(String.format("%-10s|%-10s", "awardID", "awardName"));
             rs=stmt.executeQuery("select * from award");
             while(rs.next()) {
             System.out.println(String.format("%-10s|%-10s", rs.getString(1), rs.getString(2)));
             }
             System.out.println("-----<actorObtain>-----");
             rs=stmt.executeQuery("select * from actorObtain");
             System.out.println(String.format("%-10s|%-10s|%-10s", "actorID", "awardID","year"));
             while(rs.next()) {
                 System.out.println(String.format("%-10s|%-10s|%-10s", rs.getString(1), rs.getString(2),rs.getString(3)));
                 }
             System.out.println(String.format("============================================================="));
        	

         	sql ="insert into award (awardName)VALUES('Best main actor')";
         	stmt.executeUpdate(sql);
         	sql = "insert into actorObtain(actorID,awardID,year)VALUES('1','3','2011')";
        	stmt.executeUpdate(sql);
            System.out.println(String.format("============================================================="));
             System.out.println("Statement :2.4. Johnny Depp won the ��Best main actor�� award in 2011");
             System.out.println("TranslatedSQL : insert into actorObtain(actorID,awardID,year)VALUES('1','3','2011')");
             System.out.println("TranslatedSQL : insert into award (awardName)VALUES('Best main actor')");
             System.out.println("-----<award>-----");
             System.out.println(String.format("%-10s|%-10s", "awardID", "awardName"));
             rs=stmt.executeQuery("select * from award");
             while(rs.next()) {
             System.out.println(String.format("%-10s|%-10s", rs.getString(1), rs.getString(2)));
             }
             System.out.println("-----<actorObtain>-----");
             rs=stmt.executeQuery("select * from actorObtain");
             System.out.println(String.format("%-10s|%-10s|%-10s", "actorID", "awardID","year"));
             while(rs.next()) {
                 System.out.println(String.format("%-10s|%-10s|%-10s", rs.getString(1), rs.getString(2),rs.getString(3)));
                 }
             System.out.println(String.format("============================================================="));

         	sql ="insert into award (awardName)VALUES('Best fantasy movie')";
         	stmt.executeUpdate(sql);
         	sql = "insert into movieObtain(movieID,awardID,year)VALUES('1','4','1991')";
         	stmt.executeUpdate(sql);
            System.out.println(String.format("============================================================="));
             System.out.println("Statement :2.5. Edward Scissorhands won the ��Best fantasy movie�� award in 1991");
             System.out.println("TranslatedSQL :insert into movieObtain(movieID,awardID,year)VALUES('1','4','1991')");
             System.out.println("TranslatedSQL : insert into award (awardName)VALUES('Best fantasy movie')");
             System.out.println("-----<award>-----");
             System.out.println(String.format("%-10s|%-10s", "awardID", "awardName"));
             rs=stmt.executeQuery("select * from award");
             while(rs.next()) {
             System.out.println(String.format("%-10s|%-10s", rs.getString(1), rs.getString(2)));
             }
             System.out.println("-----<movieObtain>-----");
             rs=stmt.executeQuery("select * from movieObtain");
             System.out.println(String.format("%-10s|%-10s|%-10s", "movieID", "awardID","year"));
             while(rs.next()) {
                 System.out.println(String.format("%-10s|%-10s|%-10s", rs.getString(1), rs.getString(2),rs.getString(3)));
                 }
             System.out.println(String.format("============================================================="));
        	
             
        	sql = "insert into movieObtain(movieID,awardID,year)VALUES('2','4','2011')";
        	stmt.executeUpdate(sql);
            System.out.println(String.format("============================================================="));
            System.out.println("Statement :2.6. Alice In Wonderland won the ��Best fantasy movie�� award in 2011");
            System.out.println("TranslatedSQL :insert into movieObtain(movieID,awardID,year)VALUES('2','4','2011')");
            System.out.println("-----<movieObtain>-----");
            rs=stmt.executeQuery("select * from movieObtain");
            System.out.println(String.format("%-10s|%-10s|%-10s", "movieID", "awardID","year"));
            while(rs.next()) {
                System.out.println(String.format("%-10s|%-10s|%-10s", rs.getString(1), rs.getString(2),rs.getString(3)));
                }
            System.out.println(String.format("============================================================="));

        	sql ="insert into award (awardName)VALUES('Best picture')";
        	stmt.executeUpdate(sql);
          	sql = "insert into movieObtain(movieID,awardID,year)VALUES('4','5','2009')";
          	stmt.executeUpdate(sql);
            System.out.println(String.format("============================================================="));
             System.out.println("Statement :2.7. The Dark Knight won the ��Best picture�� award in 2009");
             System.out.println("TranslatedSQL :insert into award (awardName)VALUES('Best picture')");
             System.out.println("TranslatedSQL :insert into movieObtain(movieID,awardID,year)VALUES('4','5','2009')");
             System.out.println("-----<award>-----");
             System.out.println(String.format("%-10s|%-10s", "awardID", "awardName"));
             rs=stmt.executeQuery("select * from award");
             while(rs.next()) {
             System.out.println(String.format("%-10s|%-10s", rs.getString(1), rs.getString(2)));
             }
             System.out.println("-----<movieObtain>-----");
             rs=stmt.executeQuery("select * from movieObtain");
             System.out.println(String.format("%-10s|%-10s|%-10s", "movieID", "awardID","year"));
             while(rs.next()) {
                 System.out.println(String.format("%-10s|%-10s|%-10s", rs.getString(1), rs.getString(2),rs.getString(3)));
                 }
             System.out.println(String.format("============================================================="));

         	sql ="insert into award (awardName)VALUES('Best director')";
         	stmt.executeUpdate(sql);
         	sql = "insert into directorObtain(directorID,awardID,year)VALUES('3','6','2018')";
         	stmt.executeUpdate(sql);
            System.out.println(String.format("============================================================="));
             System.out.println("Statement :2.8. Christopher Nolan won the ��Best director�� award in 2018");
             System.out.println("TranslatedSQL : insert into award (awardName)VALUES('Best director')");
             System.out.println("TranslatedSQL :insert into directorObtain(directorID,awardID,year)VALUES('3','7','2018')");
             System.out.println("-----<award>-----");
             System.out.println(String.format("%-10s|%-10s", "awardID", "awardName"));
             rs=stmt.executeQuery("select * from award");
             while(rs.next()) {
             System.out.println(String.format("%-10s|%-10s", rs.getString(1), rs.getString(2)));
             }
             System.out.println("-----<movieObtain>-----");
             rs=stmt.executeQuery("select * from directorObtain");
             System.out.println(String.format("%-10s|%-10s|%-10s", "directorID", "awardID","year"));
             while(rs.next()) {
                 System.out.println(String.format("%-10s|%-10s|%-10s", rs.getString(1), rs.getString(2),rs.getString(3)));
                 }
             System.out.println(String.format("============================================================="));
        	
        	stmt.close();
        } catch(SQLException e) {
        	e.printStackTrace();
        }
        //insert data and update avgrate
        try {
        	Statement stmt=connection.createStatement();
        	ResultSet rs;
        	String sql="insert into customerRate(customerID,movieID,rate) VALUES('1','5','5.00');\r\n" + 
        			"update movie SET avgrate='5.00' WHERE movieID=5;\r\n" ;
         	stmt.executeUpdate(sql);
         	 System.out.println(String.format("============================================================="));
             System.out.println("Statement :3.1 Ethan rates 5 to ��Dunkirk��.");
             System.out.println("TranslatedSQL : insert into customerRate(customerID,movieID,rate) VALUES('1','5','5.00')");
             System.out.println("TranslatedSQL :update movie SET avgrate='5.00' WHERE movieID=5");
             System.out.println("-----<customerRate>-----");
             System.out.println(String.format("%-20s|%-20s|%-20s", "customerID", "movieID","rate"));
             rs=stmt.executeQuery("select * from customerRate");
             while(rs.next()) {
                 System.out.println(String.format("%-20s|%-20s|%-20s", rs.getString(1), rs.getString(2),rs.getString(3)));
             }
             System.out.println("-----<movie>-----");
             rs=stmt.executeQuery("select * from movie");
             System.out.println(String.format("%-20s|%-20s", "movieID","avgRate"));
             while(rs.next()) {
                 System.out.println(String.format("%-20s|%-20s", rs.getString(1),rs.getString(7)));
                 }
             System.out.println(String.format("============================================================="));
        	
        			sql="insert into customerRate(customerID,movieID,rate) VALUES('5','1','5.00');\r\n" + 
        				"update movie SET avgrate='5.00' WHERE movieID=1;\r\n";
                 	stmt.executeUpdate(sql);
                 	sql="insert into customerRate(customerID,movieID,rate) VALUES('5','2','5.00');\r\n" + 
                			"update movie SET avgrate='5.00' WHERE movieID=2;\r\n" ; 
                     stmt.executeUpdate(sql);
                 	 System.out.println(String.format("============================================================="));
                     System.out.println("Statement :3.2 Bell rates 5 to the movies whose director is Tim Burton");
                     System.out.println("TranslatedSQL : insert into customerRate(customerID,movieID,rate) VALUES('5','1','5.00')");
                     System.out.println("TranslatedSQL : insert into customerRate(customerID,movieID,rate) VALUES('5','2','5.00')");
                     System.out.println("TranslatedSQL : update movie SET avgrate='5.00' WHERE movieID=2");
                     System.out.println("TranslatedSQL : update movie SET avgrate='5.00' WHERE movieID=1");
                     System.out.println("-----<customerRate>-----");
                     System.out.println(String.format("%-20s|%-20s|%-20s", "customerID", "movieID","rate"));
                     rs=stmt.executeQuery("select * from customerRate");
                     while(rs.next()) {
                         System.out.println(String.format("%-20s|%-20s|%-20s", rs.getString(1), rs.getString(2),rs.getString(3)));
                     }
                     System.out.println("-----<movie>-----");
                     rs=stmt.executeQuery("select * from movie");
                     System.out.println(String.format("%-20s|%-20s", "movieID","avgRate"));
                     while(rs.next()) {
                         System.out.println(String.format("%-20s|%-20s", rs.getString(1),rs.getString(7)));
                         }
                     System.out.println(String.format("============================================================="));
        			

        			sql=	"insert into customerRate(customerID,movieID,rate) VALUES('4','1','4.00');\r\n" + 
        			"update movie SET avgrate='4.50' WHERE movieID=1;\r\n" ; 
                 	stmt.executeUpdate(sql);
        			sql="insert into customerRate(customerID,movieID,rate) VALUES('4','2','4.00');\r\n" + 
        			"update movie SET avgrate='4.50' WHERE movieID=2;\r\n" ; 
                 	stmt.executeUpdate(sql);
                 	 System.out.println(String.format("============================================================="));
                     System.out.println("Statement :3.3 Jill rates 4 to the movies whose main actor is female.");
                     System.out.println("TranslatedSQL :insert into customerRate(customerID,movieID,rate) VALUES('4','1','4.00')");
                     System.out.println("TranslatedSQL :insert into customerRate(customerID,movieID,rate) VALUES('4','1','4.00')");
                     System.out.println("TranslatedSQL :insert into customerRate(customerID,movieID,rate) VALUES('4','2','4.00')");
                     System.out.println("TranslatedSQL :insert into customerRate(customerID,movieID,rate) VALUES('4','1','4.00')");
                     System.out.println("TranslatedSQL : update movie SET avgrate='4.50' WHERE movieID=1");
                     System.out.println("TranslatedSQL : update movie SET avgrate='4.50' WHERE movieID=2");
                     System.out.println("-----<customerRate>-----");
                     System.out.println(String.format("%-20s|%-20s|%-20s", "customerID", "movieID","rate"));
                     rs=stmt.executeQuery("select * from customerRate");
                     while(rs.next()) {
                         System.out.println(String.format("%-20s|%-20s|%-20s", rs.getString(1), rs.getString(2),rs.getString(3)));
                     }
                     System.out.println("-----<movie>-----");
                     rs=stmt.executeQuery("select * from movie");
                     System.out.println(String.format("%-20s|%-20s", "movieID","avgRate"));
                     while(rs.next()) {
                         System.out.println(String.format("%-20s|%-20s", rs.getString(1),rs.getString(7)));
                         }
                     System.out.println(String.format("============================================================="));
                 	
                 	
                 	
        			sql="insert into customerRate(customerID,movieID,rate) VALUES('3','1','4.00');\r\n" + 
        			"update movie SET avgrate='4.33' WHERE movieID=1;\r\n" ; 
                 	stmt.executeUpdate(sql);
        			sql="insert into customerRate(customerID,movieID,rate) VALUES('3','2','4.00');\r\n" + 
        			"update movie SET avgrate='4.33' WHERE movieID=2;\r\n" ; 
                 	stmt.executeUpdate(sql);
        			sql="insert into customerRate(customerID,movieID,rate) VALUES('3','5','5.00');\r\n" + 
        			"update movie SET avgrate='5.00' WHERE movieID=5;\r\n" ; 
                 	stmt.executeUpdate(sql);
                 	System.out.println(String.format("============================================================="));
                    System.out.println("Statement :3.4 Hayden rates 4 to the fantasy movies.");
                    System.out.println("TranslatedSQL :insert into customerRate(customerID,movieID,rate) VALUES('3','1','4.00')");
                    System.out.println("TranslatedSQL :insert into customerRate(customerID,movieID,rate) VALUES('3','2','4.00')");
                    System.out.println("TranslatedSQL :insert into customerRate(customerID,movieID,rate) VALUES('3','5','5.00')");
                    System.out.println("TranslatedSQL :update movie SET avgrate='4.33' WHERE movieID=1");
                    System.out.println("TranslatedSQL :update movie SET avgrate='4.33' WHERE movieID=2;");
                    System.out.println("TranslatedSQL :update movie SET avgrate='5.00' WHERE movieID=5");
                    System.out.println("-----<customerRate>-----");
                    System.out.println(String.format("%-20s|%-20s|%-20s", "customerID", "movieID","rate"));
                    rs=stmt.executeQuery("select * from customerRate");
                    while(rs.next()) {
                        System.out.println(String.format("%-20s|%-20s|%-20s", rs.getString(1), rs.getString(2),rs.getString(3)));
                    }
                    System.out.println("-----<movie>-----");
                    rs=stmt.executeQuery("select * from movie");
                    System.out.println(String.format("%-20s|%-20s", "movieID","avgRate"));
                    while(rs.next()) {
                        System.out.println(String.format("%-20s|%-20s", rs.getString(1),rs.getString(7)));
                        }
                    System.out.println(String.format("============================================================="));
                	
                 	
                 	
        			sql="insert into customerRate(customerID,movieID,rate) VALUES('2','4','5.00');\r\n" + 
        			"update movie SET avgrate='5.00' WHERE movieID=4;\r\n" ; 
                 	stmt.executeUpdate(sql);
        			sql="insert into customerRate(customerID,movieID,rate) VALUES('2','5','5.00');\r\n" + 
        			"update movie SET avgrate='5.00' WHERE movieID=5;\r\n";
                 	stmt.executeUpdate(sql);
                 	System.out.println(String.format("============================================================="));
                    System.out.println("Statement :3.5 John rates 5 to the movies whose director won the ��Best director�� award");
                    System.out.println("TranslatedSQL :insert into customerRate(customerID,movieID,rate) VALUES('2','4','5.00')");
                    System.out.println("TranslatedSQL :insert into customerRate(customerID,movieID,rate) VALUES('2','5','5.00')");
                    System.out.println("TranslatedSQL :update movie SET avgrate='5.00' WHERE movieID=4");
                    System.out.println("TranslatedSQL :update movie SET avgrate='5.00' WHERE movieID=5");
                    System.out.println("-----<customerRate>-----");
                    System.out.println(String.format("%-20s|%-20s|%-20s", "customerID", "movieID","rate"));
                    rs=stmt.executeQuery("select * from customerRate");
                    while(rs.next()) {
                        System.out.println(String.format("%-20s|%-20s|%-20s", rs.getString(1), rs.getString(2),rs.getString(3)));
                    }
                    System.out.println("-----<movie>-----");
                    rs=stmt.executeQuery("select * from movie");
                    System.out.println(String.format("%-20s|%-20s", "movieID","avgRate"));
                    while(rs.next()) {
                        System.out.println(String.format("%-20s|%-20s", rs.getString(1),rs.getString(7)));
                        }
                    System.out.println(String.format("============================================================="));
                	
        			
        }catch(SQLException e) {
        	e.printStackTrace();
        }
        //select , delete
        try {
        	Statement stmt=connection.createStatement();
        	ResultSet rs;
        	System.out.println(String.format("============================================================="));
            System.out.println("Statement :4. Select the names of the movies whose actor are dead.");
            System.out.println("TranslatedSQL :select movieName from movie where movieID in (select movieID from casting where actorID in (select actorID from actor where dateOfDeath is not null))");
        	String 	sql="select movieName from movie where movieID in (select movieID from casting where actorID in (select actorID from actor where dateOfDeath is not null))";
        	rs=stmt.executeQuery(sql);
            System.out.println(String.format("%-20s", "name"));
            while(rs.next()) {
            	System.out.println(String.format("%-20s",rs.getString(1)));
            }
        	System.out.println(String.format("============================================================="));
        	
        	System.out.println(String.format("============================================================="));
        	System.out.println("Statement :5. Select the names of the directors who cast the same actor more than once.");
            System.out.println("TranslatedSQL :select distinct directorname from make natural join director natural join casting group by directorname , actorid having count(actorid)>1");
            sql="select distinct directorname\r\n" + 
            		"from make natural join director natural join casting\r\n" + 
            		"group by directorname , actorid\r\n" + 
            		"having count(actorid)>1";
            rs=stmt.executeQuery(sql);
            System.out.println(String.format("%-20s", "directorname"));

            while(rs.next()) {
        	System.out.println(String.format("%-20s",rs.getString(1)));
        }
        	System.out.println(String.format("============================================================="));

      
        	System.out.println(String.format("============================================================="));
        	System.out.println("Statement :6. Select the names of the movies and the genres, where movies have the common genre.");
            System.out.println("TranslatedSQL :select distinct moviegenre.genrename,moviename"
            		+ " from movie natural join moviegenre,genre where moviegenre.genrename "
            		+ "in(select genrename from movie natural join moviegenre"
            		+ " group by genrename having count(genrename)>1");
            sql="select distinct moviegenre.genrename,moviename from movie natural join moviegenre,genre where moviegenre.genrename in(select genrename from movie natural join moviegenre group by genrename having count(genrename)>1 )order by genrename\r\n";
            rs=stmt.executeQuery(sql);
            System.out.println(String.format("%-50s|%-20s ", "genrename", "moviename"));
        	String str="";
        	System.out.print(String.format("============================================================="));

            while(rs.next()) {
            	if(!str.equals(rs.getString(1)))
            	{
            	System.out.println();
            	System.out.print(String.format("%-20s|%-20s", rs.getString(1), rs.getString(2)));
            	str=rs.getString(1);

            	}
            else {
            	System.out.print(String.format("|%-20s",rs.getString(2)));
            }
        }
            System.out.println();
        	System.out.println(String.format("============================================================="));

        	System.out.println(String.format("============================================================="));
        	System.out.println("Statement :7. Delete the movies whose director or actor did not get any award and delete data from related tables.");
        	System.out.println("TranslatedSQL :delete from customerrate where movieID = '3'");
        	System.out.println("TranslatedSQL :delete from casting  where movieID = '3'");
        	System.out.println("TranslatedSQL :delete from make where movieID = '3'");
        	System.out.println("TranslatedSQL :delete from movieGenre where movieID = '3'");
        	System.out.println("TranslatedSQL :delete from movie where movieID = '3'");

        	System.out.println(String.format("=====before=================================================="));
            System.out.println(String.format("%-20s|%-20s", "movieid","moviename"));
        	sql="select movieid,moviename from movie";
        	rs=stmt.executeQuery(sql);
        	while(rs.next()) {
            	System.out.println(String.format("%-20s|%-20s|%-20s",rs.getString(1),rs.getString(2),rs.getString(2)));

        	}
        	sql="delete from movie where movieID = '3'";
        	stmt.executeUpdate(sql);
        	sql="delete from make WHERE movieID = '3'";
        	stmt.executeUpdate(sql);
        	sql="delete from customerrate where movieID = '3'";
        	stmt.executeUpdate(sql);
        	sql="delete from movieGenre where movieID = '3'";
        	stmt.executeUpdate(sql);
        	sql="delete from casting where movieID = '3'";
        	stmt.executeUpdate(sql);
        	System.out.println(String.format("=====after=================================================="));
        	sql="select * from movie";
        	rs=stmt.executeQuery(sql);
        	while(rs.next()) {
                System.out.println(String.format("%-20s|%-20s", rs.getString(1), rs.getString(2)));
        	}
        	System.out.println(String.format("============================================================="));
        	
        	
        	System.out.println(String.format("============================================================="));
        	System.out.println("Statement :8. Delete all customers and delete data from related tables.");
        	System.out.println("TranslatedSQL :delete from customer");
        	System.out.println(String.format("=====before=================================================="));
        	System.out.println("TranslatedSQL :select * from customer");
            System.out.println(String.format("%-20s|%-20s", "customerid","customername"));
        	sql="select * from customer";
        	rs=stmt.executeQuery(sql);
        	while(rs.next()) {
                System.out.println(String.format("%-20s|%-20s", rs.getString(1), rs.getString(2)));
        	}
        	sql ="delete from customer";
        	stmt.executeUpdate(sql);
        	System.out.println(String.format("=====after=================================================="));
            System.out.println(String.format("%-20s|%-20s", "customerid","customername"));
        	System.out.println("TranslatedSQL :delete from customer");
        	sql="select * from customer";
        	rs=stmt.executeQuery(sql);
        	while(rs.next()) {
                System.out.println(String.format("%-20s|%-20s", rs.getString(1), rs.getString(2)));
        	}
        	System.out.println(String.format("============================================================="));
        	
        
        
        	stmt.close();
        	
        	}
        catch(SQLException e) {
        	e.printStackTrace();        }
        //drop table
			 try {	
		    System.out.println(String.format("============================================================="));
		    System.out.println("Statement :9. Delete all tables and data (make the database empty).");
        	System.out.println("TranslatedSQL :drop table director cascade"
        			+ ",drop table director cascade,"
        			+ ",drop table movie cascade,"
        			+ ",drop table award cascade,"
        			+ ",drop table genre cascade,"
        			+ "drop table movieGenre cascade,"
        			+ "drop table movieObtain cascade,"
        			+ "drop table actorObtain cascade,"
        			+ "drop table directorObtain cascade,"
        			+ "drop table casting cascade,"
        			+ "drop table customerRate cascade,"
        			+ "drop table customer cascade");
		    System.out.println(String.format("============================================================="));

		    Statement stmt = connection.createStatement();
			String  sql = "drop table "+ "director cascade";
			stmt.executeUpdate(sql);
			  sql = "drop table "+ "actor cascade";	
			stmt.executeUpdate(sql);
			sql = "drop table "+ "movie cascade";	
			stmt.executeUpdate(sql);
            sql = "drop table "+ "award cascade";	
			stmt.executeUpdate(sql);
			sql = "drop table "+ "genre cascade";	
			stmt.executeUpdate(sql);
			sql = "drop table "+ "movieGenre cascade";	
			stmt.executeUpdate(sql);
			sql = "drop table "+ "movieObtain cascade";	
			stmt.executeUpdate(sql);
			sql = "drop table "+ "actorObtain cascade";	
			stmt.executeUpdate(sql);
			sql = "drop table "+ "directorObtain cascade";	
			stmt.executeUpdate(sql);
		    sql = "drop table "+ "casting cascade";
			stmt.executeUpdate(sql);
			sql = "drop table "+ "make cascade";	
			stmt.executeUpdate(sql);
		    sql = "drop table "+ "customer cascade";	
			stmt.executeUpdate(sql);
		    sql = "drop table "+ "customerRate cascade";	
			stmt.executeUpdate(sql);
			stmt.close();
            connection.close();
        }
        catch (SQLException e) {
        	e.printStackTrace();
        }

    }
}