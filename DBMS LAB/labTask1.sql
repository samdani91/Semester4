drop table phone_number;
drop table modified_phone_number;

CREATE table phone_number(
    P_NUMBER varchar2(30) not null,
    id NUMBER not null,
    CONSTRAINT phone_number_pk PRIMARY KEY (P_NUMBER)
);

CREATE table modified_phone_number(
    P_NUMBER_MODIFIED varchar2(30) not null,
    CONSTRAINT modfied_phone_number_pk PRIMARY KEY (P_NUMBER_MODIFIED)
);

INSERT INTO phone_number VALUES('8004567894',1);
INSERT INTO phone_number VALUES('8004567895',2);
INSERT INTO phone_number VALUES('8004567896',3);

CREATE OR REPLACE PROCEDURE format_phone(
    p_phone_no in out varchar2
)
IS
BEGIN
p_phone_no := '(' || SUBSTR(p_phone_no,1,3) ||
                ') ' || SUBSTR(p_phone_no,4,3) ||
                '-' || SUBSTR(p_phone_no,7);
END format_phone;
/

declare
    v_phone varchar2(30);
    
BEGIN
    v_phone :='8004567894';
    format_phone(v_phone);
    DBMS_OUTPUT.PUT_LINE(v_phone);
END;
/

declare
    v_phone phone_number.P_NUMBER%type;
    
BEGIN
    select P_NUMBER into v_phone from phone_number where id=1;
    format_phone(v_phone);
    INSERT INTO modified_phone_number VALUES(v_phone);
END;
/

declare
    v_phone phone_number.P_NUMBER%type;
    
BEGIN
    select P_NUMBER into v_phone from phone_number where id=2;
    format_phone(v_phone);
    INSERT INTO modified_phone_number VALUES(v_phone);
END;
/

declare
    v_phone phone_number.P_NUMBER%type;
    
BEGIN
    select P_NUMBER into v_phone from phone_number where id=3;
    format_phone(v_phone);
    INSERT INTO modified_phone_number VALUES(v_phone);
END;
/