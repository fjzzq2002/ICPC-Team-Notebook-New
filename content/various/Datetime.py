# python datetime example
import datetime
d = datetime.datetime(2022, 12, 25)
print((d.year, d.month, d.day, d.hour, d.minute, d.second, d.microsecond))
d2 = datetime.datetime.fromtimestamp(1326244364)
dt = datetime.timedelta(days = 3, hours = 34, minutes = 56, seconds = 234, microseconds=1000001)
d = d + dt
print((d.year, d.month, d.day, d.hour, d.minute, d.second, d.microsecond))
print(d-d2) # <class 'datetime.timedelta'>, 4005 days, 14:47:11.000001
print(d.strftime("%Y/%m/%d, %H:%M:%S"))
d3 = datetime.datetime.strptime("25 December, 2022", "%d %B, %Y")
print(["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"][d3.weekday()])