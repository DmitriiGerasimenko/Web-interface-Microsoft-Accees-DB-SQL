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


AND ((t01.Дата = t02.Дата) and hour(t01.Время) = hour(t02.Время) and minute(t01.Время) = minute(t02.Время))
AND ((t01.Дата = t03.Дата) and hour(t01.Время) = hour(t03.Время) and minute(t01.Время) = minute(t03.Время))

ORDER BY t01.Дата ASC, t01.Время ASC
;


