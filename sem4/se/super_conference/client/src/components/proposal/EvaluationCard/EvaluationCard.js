import React, {useState} from 'react';
import PropTypes from 'prop-types';
import './EvaluationCard.css';
import {Card, StyledBody} from "baseui/card";
import {Checkbox} from "baseui/checkbox";
import {colorScale, gradeToText} from "../../../constants";
import {useSelector} from "react-redux";

const EvaluationCard = (props) => {
    const {grade, justification, displayCheckbox, reviewer} = props;
    const [checked, setChecked] = useState(false);
    const reviewerProfile = useSelector(state => state.user.users.find(u => u.email === reviewer));
    const reviewerName = `${reviewerProfile?.firstname} ${reviewerProfile?.lastname}`;

    const gradeStyle = {
        color: colorScale[props.grade.toString()],
        fontWeight: "bold",
        wordWrap: "break-word",
        marginRight: "1em"
    };

    return (
        <Card className={"EvaluationCard " + (checked && "fade")} data-testid="EvaluationCard">
            <StyledBody style={{display: "flex"}}>
                <div style={{width: "90%"}}>
                    <p>{justification}</p>
                    <div style={{display: "flex"}}>
                        <small style={gradeStyle}>{gradeToText[grade.toString()]}</small>
                        <small> <b style={{marginRight: '1em'}}>{`${reviewerName}`}</b> {reviewer}</small>
                    </div>
                </div>
                {
                    displayCheckbox &&
                    <div style={{width: "10%", display: "flex", justifyContent: "center", alignItems: "center"}}>
                        <Checkbox checked={checked} onChange={e => setChecked(e.target.checked)}/>
                    </div>
                }
            </StyledBody>
        </Card>
    )
};

EvaluationCard.propTypes = {
    justification: PropTypes.string.isRequired,
    grade: PropTypes.number,
    /*
        Should be true only for the use case where the
        MainAuthor wants to mark the feedback as "being accounted for"
        Thus, this prop gets a default value of false - see below
     */
    displayCheckbox: PropTypes.bool,
    // TODO WTF was this?
    // Can be made null for use cases where the author must be anonymous
    reviewerEmail: PropTypes.string
};

EvaluationCard.defaultProps = {
    displayCheckbox: false
};

export default EvaluationCard;
