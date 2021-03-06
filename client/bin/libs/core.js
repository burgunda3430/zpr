// Generated by CoffeeScript 1.6.3
(function() {
  var cancelNotification, host, hostJSON, loginSuccess, showNotification, successJSON,
    _this = this;

  this.setCookie = function(name, value, days) {
    var date, expires;
    if (days) {
      date = new Date();
      date.setTime(date.getTime() + days * 24 * 60 * 60 * 1000);
      expires = "; expires=" + (date.toGMTString());
    } else {
      expires = "";
    }
    return document.cookie = name + "=" + value + expires + "; path=/";
  };

  this.getCookie = function(name) {
    var cookie, cookies, eq, raw_cookie, _i, _len;
    cookies = document.cookie.split(';');
    for (_i = 0, _len = cookies.length; _i < _len; _i++) {
      raw_cookie = cookies[_i];
      cookie = $.trim(raw_cookie);
      eq = cookie.indexOf('=');
      if (cookie.slice(0, eq) === name) {
        return cookie.slice(eq + 1);
      }
    }
    return null;
  };

  this.deleteCookie = function(name) {
    return setCookie(name, "", -1);
  };

  host = "http://localhost:3000/";

  hostJSON = host + '/test';

  this.loadContent = function(url, parameters) {
    return $.ajax({
      type: 'POST',
      url: host + url,
      data: parameters,
      success: function(data) {
        return $("#content").replaceWith(data);
      },
      async: false
    });
  };

  this.load = function(method, requestParameters) {
    var parameters;
    parameters = [
      {
        username: username,
        method: method,
        parameters: requestParameters
      }
    ];
    return $.ajax({
      type: "POST",
      url: hostJSON,
      data: JSON.stringify(parameters),
      success: successJSON,
      error: function(_, __, text) {
        return notify("Error while connecting to server", 2500, notify.error);
      },
      timeout: 1000
    });
  };

  if (this.callback == null) {
    this.callback = [];
  }

  successJSON = function(data) {
    var method, parameters;
    if (data.error != null) {
      notify(data.error, 2500, notify.error);
      return false;
    }
    method = data.method;
    parameters = data.parameters;
    if (method in _this.callback) {
      return _this.callback[method](parameters);
    } else {
      notify("Unknown answer from server.", 2500, notify.error);
      return false;
    }
  };

  this.logIn = function() {
    var login, parameters;
    login = $('input[name=login]').val();
    if ($('input[name="remember-me"]').prop('checked')) {
      setCookie("username", login, 60);
    }
    parameters = [
      {
        "login": login
      }
    ];
    load('login', parameters, loginSuccess);
    return false;
  };

  loginSuccess = function(data) {
    this.username = data.response;
    return loadURL("/lobby.html");
  };

  $(function() {
    var login;
    _this.username = null;
    login = getCookie("username");
    if (login != null) {
      $('input[name="login"]').val(login);
      $('input[name="remember-me"]').prop('checked', true);
    } else {
      notify("<h1>Welcome</h1><div>Please sign in</div>", 3000);
    }
    return $('#form-signin').submit(logIn);
  });

  showNotification = function() {
    var notification;
    notification = $("#notification");
    notification.is('.fly-over');
    return notification.addClass('in');
  };

  cancelNotification = function() {
    var notification;
    notification = $("#notification");
    notification.removeClass('in');
    if (notification.hasClass('error')) {
      setTimeout((function() {
        return notification.removeClass('error');
      }), 200);
    }
    if (notification.hasClass('warning')) {
      return setTimeout((function() {
        return notification.removeClass('warning');
      }), 200);
    }
  };

  this.notify = function(message, time, state) {
    var notification;
    if (state == null) {
      state = notify.normal;
    }
    notification = $("#notification");
    switch (state) {
      case notify.error:
        notification.addClass('error');
        break;
      case notify.warning:
        notification.addClass('warning');
    }
    notification.html(message);
    setTimeout(showNotification, 200);
    return setTimeout(cancelNotification, 200 + time);
  };

  this.notify.normal = 0;

  this.notify.warning = 1;

  this.notify.error = 2;

  $(function() {
    var ntf;
    ntf = $('<div>');
    ntf.attr('id', 'notification');
    ntf.html('<h2>Welcome</h2><div>Please sign in</div>');
    ntf.addClass('jumbotron');
    ntf.addClass('flyover');
    ntf.addClass('flyover-centered');
    return ntf.appendTo($('body'));
  });

}).call(this);
