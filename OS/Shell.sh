#!/bin/sh
select=1
a=6
while [ "$select" -le "$a" ]
do
	echo "MENU\n 1)Create address book\n 2)View address book\n 3)Insert a record\n 4)Search a record\n 5)Delete a record\n 6)Modify a record\n 7)Exit\n Enter your choice:\c"
	read choice
	
	create()
	{
		touch File3.txt
		echo "RollNo\t Name\t Phone-Number\t Address\n">File3.txt

	}
	insert()
	{
	
		echo "RollNo:\c"
		read roll
		echo "Name:\c"
		read name
		echo "Phone:\c"
		while true
		do
			read phone
			len=$(echo -n $phone | wc -m)
			if test $len -eq 10 ; then
				break;
			else
				echo "\n Please enter a 10 digit number \n"
			fi
		done
		echo "Address:\c"
		read address
		echo "$roll\t $name\t $phone\t\t $address">>File3.txt #Passing values to File3
	}

	search()
	{
		echo "Enter the phone number to be searched:\c" #Searching a record by the phone number
		read phon2
		grep -q $phon2 File3.txt #Searches in File3
		if [ $? -ne 0 ]
		then
			echo "Record Not found"
		else
			grep -i -w "$phon2" File3.txt
			echo "Record found"
		fi

		
	}
	delete()
	{
		
		echo "Enter the phone number to be deleted:\c" #Deletion of records
		read phon
		grep -q -w $phon File3.txt #Searches for the entered record
		if [ $? -ne 0 ]
		then
			echo "Record Not found"
		else
			grep -v -i -w "$phon" File3.txt>File2.txt
			mv File2.txt File3.txt
			echo "Record Deleted"
		fi
	

	}

	modify()
	{
		echo "Enter the phone number to be modified:\c" #Modify the record from File3
		read phon1
		grep -q -w $phon1 File3.txt
		if [ $? -ne 0 ]
		then
			echo "Record Not found"
		else
			grep  -v -i -q -w "$phon1" File3.txt>q.txt #Passing the non selected records to q.txt
			mv q.txt File3.txt #Get all the records back to File3
			insert
		fi
	}

	case "$choice" in
	1)create;; #Creating File3
	
	
	2)cat File3.txt;;
	
	3)
		x=1
		y=1
		while [ "$x" -eq "$y" ]
		do	
			insert
			echo "Do you want to add another record \nPress 1 to continue \nPress 2 to discontinue->\c"
			read x
		done
	;;
	
	4)search;;
	
		
	5)delete;;
	
	
	6)modify;;
	
	7)exit;;
	*)echo "Invalid choice!!!";;
	esac
done
