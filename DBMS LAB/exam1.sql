DROP TABLE RESERVES;
DROP TABLE BOATS;
DROP TABLE SAILORS;

CREATE TABLE SAILORS(
    SID NUMBER NOT NULL,
    SNAME VARCHAR2(25) NOT NULL,
    RATING NUMBER NOT NULL,
    AGE NUMBER NOT NULL,
    CONSTRAINT SAILORS_PK PRIMARY KEY (SID)
);

CREATE TABLE BOATS(
    BID NUMBER NOT NULL,
    BNAME VARCHAR2(25) NOT NULL,
    COLOR VARCHAR2(25) NOT NULL,
    CONSTRAINT BOATS_PK PRIMARY KEY (BID)
);

CREATE TABLE RESERVES(
    SID NUMBER NOT NULL,
    BID NUMBER NOT NULL,
    DAY DATE,
    CONSTRAINT RESERVES_PK PRIMARY KEY (SID,BID),
    CONSTRAINT RESERVES_FK1 FOREIGN KEY (SID) REFERENCES SAILORS (SID),
    CONSTRAINT RESERVES_FK2 FOREIGN KEY (BID) REFERENCES BOATS (BID)
);

INSERT INTO SAILORS VALUES (22,'Dustin',7,45.0);
INSERT INTO SAILORS VALUES (29,'Brutus',1,33.0);
INSERT INTO SAILORS VALUES (31,'Lubber',8,55.5);
INSERT INTO SAILORS VALUES (32,'Andy',8,25.5);
INSERT INTO SAILORS VALUES (58,'Rusty',10,35.0);
INSERT INTO SAILORS VALUES (64,'Horatio',7,35.0);
INSERT INTO SAILORS VALUES (71,'Zorba',10,16.0);
INSERT INTO SAILORS VALUES (74,'Horatio',9,35.0);
INSERT INTO SAILORS VALUES (85,'Art',3,25.5);
INSERT INTO SAILORS VALUES (95,'Bob',3,63.5);

INSERT INTO BOATS VALUES (101,'Interlake','blue');
INSERT INTO BOATS VALUES (102,'Interlake','red');
INSERT INTO BOATS VALUES (103,'Clipper','green');
INSERT INTO BOATS VALUES (104,'Marine','red');


INSERT INTO RESERVES VALUES (22,101, TO_DATE('10/10/98','MM/DD/YY'));
INSERT INTO RESERVES VALUES (22,102, TO_DATE('10/10/98','MM/DD/YY'));
INSERT INTO RESERVES VALUES (22,103, TO_DATE('10/8/98','MM/DD/YY'));
INSERT INTO RESERVES VALUES (22,104, TO_DATE('10/7/98','MM/DD/YY'));
INSERT INTO RESERVES VALUES (31,102, TO_DATE('11/10/98','MM/DD/YY'));
INSERT INTO RESERVES VALUES (31,103, TO_DATE('11/6/98','MM/DD/YY'));
INSERT INTO RESERVES VALUES (31,104, TO_DATE('11/12/98','MM/DD/YY'));
INSERT INTO RESERVES VALUES (64,101, TO_DATE('9/5/98','MM/DD/YY'));
INSERT INTO RESERVES VALUES (64,102, TO_DATE('9/8/98','MM/DD/YY'));
INSERT INTO RESERVES VALUES (74,103, TO_DATE('9/8/98','MM/DD/YY'));

--1st Q
select  SNAME from SAILORS,RESERVES where SAILORS.SID=RESERVES.SID and RESERVES.BID=103;

--2nd Q
select   SNAME from SAILORS,RESERVES where SAILORS.SID=RESERVES.SID and RESERVES.BID IN(select BID from BOATS where COLOR='red');

--3rd Q
select distinct color from SAILORS s,RESERVES r,BOATS b where s.SID=r.SID and r.BID=b.BID and SNAME='Lubber';

--4th Q
select SNAME from SAILORS where sid in (select sid from RESERVES);

--5th Q


-- Find the names of sailors who have reserved a red boat, and list in the order of age
select sname,age from SAILORS s,RESERVES r,BOATS b
where
s.sid=r.sid and r.bid=b.bid and b.color='red'
order By 
s.age;

--. Find the ids and names of sailors who have reserved two different boats on the same day
select distinct s.sid,sname from  SAILORS s,RESERVES r1,RESERVES r2 
where s.sid=r1.sid and s.sid=r2.sid and r1.day=r2.day and r1.bid<>r2.bid;

--Find the ids of sailors who have reserved a red boat or a green boat.
select sid from RESERVES r,BOATS b
where r.bid=b.bid and b.color='red'
UNION ALL
select sid from RESERVES r2,BOATS b2 
where r2.bid=b2.bid and b2.color='green';

--Find the name and the age of the youngest sailor
select sname from SAILORS
where age<=ALL(select age from SAILORS);

--Find the names and ratings of sailor whose rating is better than some sailor called Horatio.
select sname,rating from SAILORS
where rating > ANY(select rating from SAILORS where sname='Horatio');

--Find the names of sailors who have reserved all boats
select s.sname from SAILORS s 
where NOT EXISTS (
    (select b.bid from BOATS b)
    MINUS
    (select r.bid from RESERVES r where r.sid=s.sid)
);
