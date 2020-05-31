import React from 'react';
import './Dashboard.css';
import Navbar from "../../navigation/Navbar/Navbar";
import {Route, Switch} from "react-router-dom";
import NotificationSection from "../../notification/NotificationSection/NotificationSection";
import ProposalSection from "../../proposal/ProposalSection/ProposalSection";
import ConferenceSection from "../../conference/ConferenceSection/ConferenceSection";
import NotFound from "../../navigation/NotFound/NotFound";

const Dashboard = () => {
    return (
        <div className="Dashboard" data-testid="Dashboard">
            <Navbar/>
            <Switch>
                <Route exact path={'/dashboard'} component={NotificationSection}/>

                <Route exact path={'/dashboard/proposals/:section'} component={ProposalSection}/>

                <Route exact path={'/dashboard/conferences/:section'} component={ConferenceSection}/>

                <Route path={'*'} component={NotFound}/>
            </Switch>
        </div>
    );
};

Dashboard.propTypes = {};

Dashboard.defaultProps = {};

export default Dashboard;
