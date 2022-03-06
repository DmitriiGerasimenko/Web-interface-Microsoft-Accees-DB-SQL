SELECT 
t01.Дата, 
t01.Время, 
t01.Значение AS [*1],
t02.Значение AS [*2],
t03.Значение AS [*3],
t04.Значение AS [*4],
t05.Значение AS [*5],
t06.Значение AS [*6],
t07.Значение AS [*7],
t08.Значение AS [*8],
t09.Значение AS [*9],
t10.Значение AS [*10],
t11.Значение AS [*11],
t12.Значение AS [*12],
t13.Значение AS [*13]

FROM <#TABLE_NAME1> t01, <#TABLE_NAME2> t02, <#TABLE_NAME3> t03, <#TABLE_NAME4> t04, <#TABLE_NAME5> t05, <#TABLE_NAME6> t06, <#TABLE_NAME7> t07, <#TABLE_NAME8> t08, <#TABLE_NAME9> t09, <#TABLE_NAME10> t10, <#TABLE_NAME11> t11, <#TABLE_NAME12> t12, <#TABLE_NAME13> t13

WHERE 

(t01.Дата + t01.Время) BETWEEN 
(#<#FROM_MONTH>/<#FROM_DAY>/<#FROM_YEAR># + #<#FROM_HOUR>.<#FROM_MINUTE>#) 
AND 
(#<#TO_MONTH>/<#TO_DAY>/<#TO_YEAR># + #<#TO_HOUR>.<#TO_MINUTE>#)



AND (t01.KeyID = t02.KeyID)
AND (t01.KeyID = t03.KeyID)
AND (t01.KeyID = t04.KeyID)
AND (t01.KeyID = t05.KeyID)
AND (t01.KeyID = t06.KeyID)
AND (t01.KeyID = t07.KeyID)
AND (t01.KeyID = t08.KeyID)
AND (t01.KeyID = t09.KeyID)
AND (t01.KeyID = t10.KeyID)
AND (t01.KeyID = t11.KeyID)
AND (t01.KeyID = t12.KeyID)
AND (t01.KeyID = t13.KeyID)

ORDER BY t01.KeyID ASC
;
