#COMPUTER SCIENCE PROJECT
import pickle
f=open('Student.dat','ab')
f.close()
#-----------------------------------------------------------------------------------
def create_rec():
    f1=open('Student.dat','rb')
    d={}
    lst=[]
    try:
        while True:
            i=pickle.load(f1)
            lst.append(i['admno'])
    except EOFError:
        f1.close()

    f2=open('Student.dat','ab')
    while True:
        name=input("Enter Name:")
        admno=input("Enter Admission number:")
        if admno not in lst:
            lst.append(admno)
        else:
            print("Record with this admission number already exists!")
            break
        pmark=int(input("Enter Marks out of 100 in Physics:"))
        cmark=int(input("Enter Marks out of 100 in TMI:"))
        mmark=int(input("Enter Marks out of 100 in Maths:"))
        emark=int(input("Enter Marks out of 100 in HSI:"))
        csmark=int(input("Enter Marks out of 100 in Mechanics:"))
        
        aggregate=(pmark+cmark+mmark+emark+csmark)/5
        cgpa=(pmark*4+cmark*4+mmark*4+emark*3+csmark*4)/190
        #update dictionary
        d['name']=name
        d['admno']=admno
        d['pmark']=pmark
        d['cmark']=cmark
        d['mmark']=mmark
        d['emark']=emark
        d['csmark']=csmark
        d['agg']=aggregate
        d['cgpa']=cgpa

        #storing in a file
        pickle.dump(d,f2)
        print("Student record succesfully created!")

        #asking if more records to be entered
        ask=input("Do you want to input more records?(Y/N)")
        if ask=="Y":
            continue
        elif ask=='N':
            break
        else:
            print("Enter Y for yes and N for No.")
    f2.close()

#---------------------------------------------------------------------------------------------
def delete_rec():
    #Taking input of record to be deleted
    rec=input("Enter the admission number of the student whose record is to be deleted")
    f=0
    #Creating a separate file to store non-deleted data
    f3=open("Student2.dat",'wb')

    #Deleting the specified record
    f2=open ('Student.dat','rb')
    try:
        while True:
            i=pickle.load(f2)
            if i['admno']==rec:
                f=1
                pass
            else:
                pickle.dump(i,f3)
    except EOFError:
        f2.close()
        f3.close()

    f5=open('Student.dat','wb')
    f4=open('Student2.dat','rb')
    try:
        while True:
            j=pickle.load(f4)
            pickle.dump(j,f5)
    except EOFError:
        f4.close()
        f5.close()
    #Informing the user about deletion of record
    if f==0:
        print("Student record not found!")
    else:
        print("Student record sucessfully deleted.")

#------------------------------------------------------------------------------------------------------------------
def modify_rec():
    adm=input("Enter admission number of student whose details are to be changed:")
    f2=open ('Student.dat','rb+')
    try:
        while True:
            pntr=f2.tell()
            i=pickle.load(f2)
            if i['admno']==adm:
                f=1
                name=input("Enter updated Name:")
                pmark=int(input("Enter new Marks in Physics:"))
                cmark=int(input("Enter new Marks in TMI:"))
                mmark=int(input("Enter new Marks in Maths:"))
                emark=int(input("Enter new Marks in HSI:"))
                csmark=int(input("Enter new Marks in Mechanics:"))
                aggregate=(pmark+cmark+mmark+emark+csmark)/5
                cgpa=(pmark*4+cmark*4+mmark*4+emark*3+csmark*4)/230
    
                d={}
                d['name']=name
                d['pmark']=pmark
                d['cmark']=cmark
                d['mmark']=mmark
                d['emark']=emark
                d['csmark']=csmark
                d['agg']=aggregate
                d["cgpa"]=cgpa

                i.update(d)
                f2.seek(pntr)
                pickle.dump(i,f2)
                
    except EOFError:
        f2.close()
        if f==0:
            print("Student record not found!")
        else:
            print("Student record successfully modified!")
#----------------------------------------------------------------------------
def search():
    f=0
    sd=input("Enter the admission no of student to get details : ")
    f1=open ('Student.dat','rb')
    try:
        while True:
            i=pickle.load(f1)
            if i["admno"]==sd:
                f=1
                print("\nSTUDENT REPORT")
                print("Admission NO. : ", i['admno'])
                print("NAME : ",i['name'])
                print("MARKS IN FOLLOWING SUBJECTS : ")
                print("PHYSICS   : ",i['pmark'])
                print("TMI : ",i['cmark'])
                print("MATHS     : ",i['mmark'])
                print("HSI  : ",i['emark'])
                print("MECHANICS : ",i['csmark'])
                print("CGPA : ",i['cgpa'])
                print("Aggregate percentage : ",((i['pmark']+i['cmark']+i['mmark']+i['emark']+i['csmark'])/5),"%")
    except EOFError:
        f1.close()
        if f==0:
            print("No such record found!")

#----------------------------------------------------------------------------
def display():
    #displaying result of all students
    f1=open("student.dat",'rb')
    l=[]
    c=0
    try:
        print("AGGREGATE PERCENTAGE OF STUDENTS: ")
        while True:
            i=pickle.load(f1)
            print(i['admno'],i['name'],"has cgpa",i['cgpa'])
            c+=1
            l.append(i['agg'])
    except EOFError:
        f1.close()
    avg=sum(l)/c
    print("DATA DISPLAYED!")
#----------------------------------------------------------------------------
def fail():
    f1=open("student.dat",'rb')
    c=0
    try:
        print("FOLLOWING STUDENTS HAVE FAILED: ")
        while True:
            i=pickle.load(f1)
            if (i['agg'])<=33:
                print(i['admno'],i['name'],"has failed")
                c+=1
    except EOFError:
        f1.close()
        if c==0:
            print("No one failed.")
        else:
            print("Total students failed : ",c)
#----------------------------------------------------------------------------

def merit():
    print("First 3 rank holders are:")
    f=open('Student.dat','rb')
    l=[]
    b=[]
    try:
        while True:
            i=pickle.load(f)
            l.append(i['cgpa'])
    except EOFError:
        f.close()
        for i in l:
            if i not in b:
                b.append(i)
        b=sorted(b,reverse=True)
    l1=[]
    l2=[]
    l3=[]
    
    f1=open('Student.dat','rb')
    try:
        while True:
            j=pickle.load(f1)
            if j['cgpa']==b[0]:
                det=j['admno']+" "+j['name']
                l1.append(det)
            if j['cgpa']==b[1]:
                det=j['admno']+" "+j['name']
                l2.append(det)
            if j['cgpa']==b[2]:
                det=j['admno']+" "+j['name']
                l3.append(det)
    except EOFError:
        f.close()
    print("Student(s) holding rank 1:")
    for i in l1:
        print(i)
    print("Student(s) holding rank 2:")
    for i in l2:
        print(i)
    print("Student(s) holding rank 3:")
    for i in l3:
        print(i)
    print("Congratulations to all the students!")
#------------------------------------------------------------------------------

#MAIN DISPLAY MENU
    
def intro():
    print("="*70)
    print("STUDENT DATA MANAGEMENT SYSTEM")
    print("REPORT DATA OF STUDENTS OF IIT Roorkee FOR 1st SEM")
    print("="*70)
    print()
#Main Menu
def main_menu():
    print("\nMAIN MENU")
    print("1. REPORT MENU")
    print("2. ADMIN MENU")
    print("3. EXIT")
#REPORT MENU
def report_menu():
    print("\nREPORT MENU")
    print("1. CLASS RESULT")
    print("2. LIST OF STUDENTS WITH MERIT")
    print("3. LIST OF STUDENTS WHO FAILED")
    print("4. BACK TO MAIN MENU")
#ADMIN MENU
def admin_menu():
    print("\nADMIN MENU")
    print("1.CREATE STUDENT RECORD")
    print("2.SEARCH STUDENT RECORD")
    print("3.MODIFY STUDENT RECORD")
    print("4.DELETE STUDENT RECORD")
    print("5. BACK TO MAIN MENU")

#----------------------------------------------------------------------------
    
#calling functions
def main():
    intro()
    while True:
        main_menu()
        choice=int(input("ENTER CHOICE 1-3 : "))
        print()
        if choice ==1:
                   while True:
                       report_menu()
                       rchoice=int(input("Enter choice 1-5 :"))
                       print()
                       if rchoice==1:
                                   display()
                       elif rchoice==2:
                                   merit()
                       elif rchoice==3:
                                   fail()                               
                       elif rchoice==4:
                                   break
                       else:
                           print("INVALID INPUT!!!")
                       print()
        elif choice ==2:
                   while True:
                       admin_menu()
                       rchoice=int(input("Enter choice 1-5 : "))
                       print()
                       if rchoice==1:
                                   create_rec()
                       elif rchoice==2:
                                   search()
                       elif rchoice==3:
                                   modify_rec()
                       elif rchoice==4:
                                   delete_rec()
                       elif rchoice==5:
                                   break
                       else:
                           print("INVALID INPUT!!!")
                       print()
                       
        elif choice==3:
            print("THANKS FOR USING STUDENT DATABASE MANAGEMENT SYSTEM")
            break
        else:
            print("INVALID INPUT!!!")
            print()

#calling main function
            
main()
