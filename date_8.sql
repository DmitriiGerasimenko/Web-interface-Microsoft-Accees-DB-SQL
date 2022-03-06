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
t08.Значение AS [*8]

FROM <#TABLE_NAME1> t01, <#TABLE_NAME2> t02, <#TABLE_NAME3> t03, <#TABLE_NAME4> t04, <#TABLE_NAME5> t05, <#TABLE_NAME6> t06, <#TABLE_NAME7> t07, <#TABLE_NAME8> t08


WHERE 
(t01.Дата BETWEEN #<#FROM_MONTH>/<#FROM_DAY>/<#FROM_YEAR># and #<#TO_MONTH>/<#TO_DAY>/<#TO_YEAR>#)


AND (t01.Дата = t02.Дата)
AND (t01.Дата = t03.Дата)
AND (t01.Дата = t04.Дата)
AND (t01.Дата = t05.Дата)
AND (t01.Дата = t06.Дата)
AND (t01.Дата = t07.Дата)
AND (t01.Дата = t08.Дата)

ORDER BY t01.Дата ASC
;
