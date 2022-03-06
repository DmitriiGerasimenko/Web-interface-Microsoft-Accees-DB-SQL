SELECT 
t01.����, 
t01.�����, 
t01.�������� AS [*1],
t02.�������� AS [*2],
t03.�������� AS [*3],
t04.�������� AS [*4],
t05.�������� AS [*5],
t06.�������� AS [*6],
t07.�������� AS [*7],
t08.�������� AS [*8],
t09.�������� AS [*9],
t10.�������� AS [*10],
t11.�������� AS [*11],
t12.�������� AS [*12],
t13.�������� AS [*13],
t14.�������� AS [*14],
t15.�������� AS [*15]

FROM <#TABLE_NAME1> t01, <#TABLE_NAME2> t02, <#TABLE_NAME3> t03, <#TABLE_NAME4> t04, <#TABLE_NAME5> t05, <#TABLE_NAME6> t06, <#TABLE_NAME7> t07, <#TABLE_NAME8> t08, <#TABLE_NAME9> t09, <#TABLE_NAME10> t10, <#TABLE_NAME11> t11, <#TABLE_NAME12> t12, <#TABLE_NAME13> t13, <#TABLE_NAME14> t14, <#TABLE_NAME15> t15

WHERE 
(t01.���� BETWEEN #<#FROM_MONTH>/<#FROM_DAY>/<#FROM_YEAR># and #<#TO_MONTH>/<#TO_DAY>/<#TO_YEAR>#)


AND (t01.���� = t02.����)
AND (t01.���� = t03.����)
AND (t01.���� = t04.����)
AND (t01.���� = t05.����)
AND (t01.���� = t06.����)
AND (t01.���� = t07.����)
AND (t01.���� = t08.����)
AND (t01.���� = t09.����)
AND (t01.���� = t10.����)
AND (t01.���� = t11.����)
AND (t01.���� = t12.����)
AND (t01.���� = t13.����)
AND (t01.���� = t14.����)
AND (t01.���� = t15.����)

ORDER BY t01.���� ASC
;
