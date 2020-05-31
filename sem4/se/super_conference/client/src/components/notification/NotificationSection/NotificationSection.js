import React from 'react';
import './NotificationSection.css';
import {Heading, HeadingLevel} from "baseui/heading";
import NotificationList from "../NotificationList/NotificationList";

const NotificationSection = () => (
    <div className="NotificationSection" data-testid="NotificationSection">
        <HeadingLevel>
            <Heading>Notifications</Heading>
            <NotificationList/>
        </HeadingLevel>
    </div>
);

NotificationSection.propTypes = {};

NotificationSection.defaultProps = {};

export default NotificationSection;
