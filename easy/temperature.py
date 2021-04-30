t,a,p=0,abs,input
p()
for i in p().split():    
  i=int(i)
  if a(i)==a(t):
    t=i if i>0 else t
  else:
    t=i if a(i)<a(t) or t==0 else t
print(t)