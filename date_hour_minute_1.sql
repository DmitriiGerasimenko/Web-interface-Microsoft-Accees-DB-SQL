SELECT 
t01.Дата, 
t01.Время, 
t01.Значение AS [*1]

FROM <#TABLE_NAME1> t01

WHERE 

(t01.Дата + t01.Время) BETWEEN 
(#<#FROM_MONTH>/<#FROM_DAY>/<#FROM_YEAR># + #<#FROM_HOUR>.<#FROM_MINUTE>#) 
AND 
(#<#TO_MONTH>/<#TO_DAY>/<#TO_YEAR># + #<#TO_HOUR>.<#TO_MINUTE>#)


ORDER BY t01.Дата ASC, t01.Время ASC
;


