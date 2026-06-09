select b1.ime as b1, b2.ime as b2
from bend b1
join bend b2 on b1.godina_osnovanje = b2.godina_osnovanje and b1.id < b2.id;