import React from 'react';
import './ConferenceCard.css';
import {useDispatch, useSelector} from "react-redux";
import {Card, StyledAction, StyledBody} from "baseui/card";
import {UPDATE_CONTEXT_CONFERENCE} from "../../../redux/context/contextActions";
import {Button} from "baseui/button";

const ConferenceCard = (props) => {
    const dispatch = useDispatch();
    let {conference, navProps, setModalOpen} = props;
    const {subsection} = navProps?.match.params;

    let email = useSelector(state => state.auth.email);

    // Button logic
    let buttonText = '';
    switch (subsection) {
        case 'my-conferences':
            buttonText = 'Update Conference';
            break;
        case 'add-section':
            buttonText = 'Add Section';
            break;
        case 'attend-conference':
            const hasAttended = conference.participants.includes(email);
            buttonText = hasAttended ? 'Cancel attendance' : 'Attend Conference';
            break;
        case 'upload-presentation':
            buttonText = 'Upload Presentation';
            break;
        default:
            console.assert(false, 'ConferenceCard btn text switch reached');
            break;
    }

    let deadlines = [
        ['Zero Deadline', conference?.zeroDeadline],
        ['Abstract Deadline', conference?.abstractDeadline],
        ['Proposal Deadline', conference?.proposalDeadline],
        ['Bidding Deadline', conference?.biddingDeadline],
        ['Evaluation Deadline', conference?.evaluationDeadline],
        ['Presentation Deadline', conference?.presentationDeadline],
    ];

    return (
        <Card
            title={conference?.title}
            overrides={{Root: {style: () => ({width: "50%"})}}}
        >
            <StyledBody>
                <div>{conference.description}</div>
                <div className={'CardConferenceDeadlines'}>
                    {
                        deadlines.map((d, idx) => {
                            let date = (new Date(d[1])).toLocaleDateString('en-GB');
                            return <div key={idx}><b>{d[0]}</b> {date}</div>
                        })
                    }
                </div>
            </StyledBody>
            <StyledAction>
                <Button
                    overrides={{BaseButton: {style: {width: '100%'}}}}
                    onClick={() => {
                        console.log('AAAA');
                        dispatch({
                            type: UPDATE_CONTEXT_CONFERENCE,
                            payload: {conference: conference}
                        });
                        setModalOpen(true);
                    }}>
                    {buttonText}
                </Button>
            </StyledAction>
        </Card>
    );
};

ConferenceCard.propTypes = {};

ConferenceCard.defaultProps = {};

export default ConferenceCard;
