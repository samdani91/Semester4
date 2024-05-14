set serveroutput on;

-- declare
--     cursor c_zip is
--     select * from employees;
--     vr_zip c_zip%rowtype;

-- BEGIN
--     open c_zip;
--     loop
--         fetch c_zip into vr_zip;
--         exit when c_zip%notfound;
--         DBMS_OUTPUT.PUT_LINE(vr_zip.employee_id);
--     end loop;
-- end;
-- /

declare
    cursor c_zip is
    select * from employees;
    vr_zip c_zip%rowtype;

BEGIN
    open c_zip;
    loop
        fetch c_zip into vr_zip;
        while c_zip%found 
        loop
            DBMS_OUTPUT.PUT_LINE(vr_zip.employee_id);
            fetch c_zip into vr_zip;
    end loop; 
end;
/