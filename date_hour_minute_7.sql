SELECT 
t01.Дата, 
t01.Время, 
t01.Значение AS [*1],
t02.Значение AS [*2],
t03.Значение AS [*3],
t04.Значение AS [*4],
t05.Значение AS [*5],
t06.Значение AS [*6],
t07.Значение AS [*7]

FROM <#TABLE_NAME1> t01, <#TABLE_NAME2> t02, <#TABLE_NAME3> t03, <#TABLE_NAME4> t04, <#TABLE_NAME5> t05, <#TABLE_NAME6> t06, <#TABLE_NAME7> t07


WHERE 

(t01.Дата + t01.Время) BETWEEN 
(#<#FROM_MONTH>/<#FROM_DAY>/<#FROM_YEAR># + #<#FROM_HOUR>.<#FROM_MINUTE>#) 
AND 
(#<#TO_MONTH>/<#TO_DAY>/<#TO_YEAR># + #<#TO_HOUR>.<#TO_MINUTE>#)


AND ((t01.Дата = t02.Дата) and hour(t01.Время) = hour(t02.Время) and minute(t01.Время) = minute(t02.Время))
AND ((t01.Дата = t03.Дата) and hour(t01.Время) = hour(t03.Время) and minute(t01.Время) = minute(t03.Время))
AND ((t01.Дата = t04.Дата) and hour(t01.Время) = hour(t04.Время) and minute(t01.Время) = minute(t04.Время))
AND ((t01.Дата = t05.Дата) and hour(t01.Время) = hour(t05.Время) and minute(t01.Время) = minute(t05.Время))
AND ((t01.Дата = t06.Дата) and hour(t01.Время) = hour(t06.Время) and minute(t01.Время) = minute(t06.Время))
AND ((t01.Дата = t07.Дата) and hour(t01.Время) = hour(t07.Время) and minute(t01.Время) = minute(t07.Время))

ORDER BY t01.Дата ASC, t01.Время ASC
;


