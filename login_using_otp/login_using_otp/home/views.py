from django.shortcuts import render,redirect,HttpResponse
from django.contrib.auth.models import User
from django.contrib.auth import authenticate
from django.contrib.auth import logout,login
from django.contrib import messages



# Create your views here.

def index(request):
    if request.user.is_anonymous:
        return render(request,'index.html')
    return render(request,'home.html')

def home(request):
    return render(request,'home.html')

def signup(request):
    if request.method=="POST":
        fullname = request.POST['fullname']
        user_name = request.POST.get('username')
        email = request.POST.get('email')
        password = request.POST.get('password')
        myuser = User.objects.create_user(username=user_name,email=email,password=password)
        myuser.save()
    return render(request,'sign_up.html')

def signin(request):
    if request.method=="POST":
        username = request.POST.get('username')
        password = request.POST.get('password')
        user = authenticate(request,username=username, password=password)
        if user is not None:
            login(request,user)
            return redirect("/home")
        else:
            messages.error(request,"You credentials are wrong. ")
            return render(request,'sign_in.html')

    return render(request,'sign_in.html')

def verify_OTP(request):
    return render(request,'verify_otp.html')

def create_password(request):
    return render(request,'create_password.html')

def logoutUser(request):
    logout(request)
    return render(request,'index.html')



    

