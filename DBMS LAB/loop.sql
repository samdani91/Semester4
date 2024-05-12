set serveroutput on;

--loop
-- declare
--     v_counter NUMBER:=1;
-- BEGIN
--     loop
--         if MOD(v_counter,2)!=0
--         then
--         DBMS_OUTPUT.PUT_LINE(v_counter);
--         end if;
--         v_counter := v_counter+ 1;

--         if v_counter > 10
--         then exit;
--         end if;      
--     end loop;
-- end;
-- /

--while
-- declare
--     v_counter NUMBER:=1;
-- BEGIN
--     while v_counter<=10
--     loop
--         if MOD(v_counter,2)!=0
--         then
--         DBMS_OUTPUT.PUT_LINE(v_counter||' ');
--         end if;
--         v_counter := v_counter+ 1;      
--     end loop;
-- end;
-- /

--for
-- BEGIN
--     for v_counter in 1..10
--     loop
--         if MOD(v_counter,2)!=0
--         then
--         DBMS_OUTPUT.PUT_LINE(v_counter||' ');
--         end if;      
--     end loop;
-- end;
-- /