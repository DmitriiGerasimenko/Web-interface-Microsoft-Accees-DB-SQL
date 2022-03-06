SELECT 
t01.Дата, 
t01.Время, 
t01.Значение AS [*1],
t02.Значение AS [*2],
t03.Значение AS [*3]

FROM <#TABLE_NAME1> t01, <#TABLE_NAME2> t02, <#TABLE_NAME3> t03

WHERE 

(t01.Дата + t01.Время) BETWEEN 
(#<#FROM_MONTH>/<#FROM_DAY>/<#FROM_YEAR># + #<#FROM_HOUR>.<#FROM_MINUTE>#) 
AND 
(#<#TO_MONTH>/<#TO_DAY>/<#TO_YEAR># + #<#TO_HOUR>.<#TO_MINUTE>#)



AND (t01.KeyID = t02.KeyID)
AND (t01.KeyID = t03.KeyID)

ORDER BY t01.KeyID ASC
;
