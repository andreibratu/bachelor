import React from 'react';
import './NotificationList.css';
import NotificationCard from "../NotificationCard/NotificationCard";

const NotificationList = () => {
  const notifications = [
    {
      id: 1,
      href: '/dashboard/proposals/my-proposals',
      read: false,
      text: 'This notification will send you to proposals'
    },
    {
      id: 2,
      href: '/dashboard/conferences/my-conferences',
      read: true,
      text: 'This notification will send you to conferences'
    }
  ];

  return (
      <div className="NotificationList" data-testid="NotificationList">
        {notifications.map(notification => {
              const {id, ...props} = notification;
              return <NotificationCard key={id} {...props}/>
            }
        )}
      </div>
  );
};

NotificationList.propTypes = {};

NotificationList.defaultProps = {};

export default NotificationList;
