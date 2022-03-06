SELECT 
t01.Дата, 
t01.Время, 
t01.Значение AS [*1]

FROM <#TABLE_NAME1> t01

WHERE 
(t01.Дата BETWEEN #<#FROM_MONTH>/<#FROM_DAY>/<#FROM_YEAR># and #<#TO_MONTH>/<#TO_DAY>/<#TO_YEAR>#)

ORDER BY t01.Дата ASC
;
