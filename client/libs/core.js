// Generated by CoffeeScript 1.6.3
(function() {
  var cancelNotification, showNotification;

  showNotification = function() {
    var notification;
    notification = $("#notification");
    notification.is('.fly-over');
    return notification.addClass('in');
  };

  cancelNotification = function() {
    var notification;
    notification = $("#notification");
    return notification.removeClass('in');
  };

  this.notify = function(message, time) {
    var notification;
    notification = $("#notification");
    notification.html(message);
    setTimeout(showNotification, 200);
    return setTimeout(cancelNotification, 200 + time);
  };

}).call(this);