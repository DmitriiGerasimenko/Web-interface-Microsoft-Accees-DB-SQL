SELECT 
t01.Дата, 
t01.Время, 
t01.Значение AS [*1],
t02.Значение AS [*2]

FROM <#TABLE_NAME1> t01, <#TABLE_NAME2> t02

WHERE 
(t01.Дата BETWEEN #<#FROM_MONTH>/<#FROM_DAY>/<#FROM_YEAR># and #<#TO_MONTH>/<#TO_DAY>/<#TO_YEAR>#)


AND (t01.Дата = t02.Дата)

ORDER BY t01.Дата ASC
;
