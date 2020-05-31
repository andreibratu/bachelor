import React from 'react';
import './NotificationCard.css';
import {Card, StyledBody} from "baseui/card";
import PropTypes from 'prop-types';
import {useHistory} from "react-router";

const NotificationCard = (props) => {
    const {text, href, read} = props;
    let history = useHistory();
    return (
        <div className="NotificationCard" data-testid="NotificationCard" onClick={() => history.push(href)}>
            <Card
                // @ts-ignore
                overrides={!read && {
                    Root: {
                        style: ({$theme}) => {
                            return {
                                outline: `${$theme.colors.black} solid`
                            };
                        }
                    }
                }}
            >
                <StyledBody>
                    {text}
                </StyledBody>
            </Card>
        </div>
    );
};

NotificationCard.propTypes = {
    id: PropTypes.number,
    text: PropTypes.string,
    href: PropTypes.string,
    read: PropTypes.bool
};

NotificationCard.defaultProps = {};

export default NotificationCard;
