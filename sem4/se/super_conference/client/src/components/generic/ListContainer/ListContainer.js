import React from 'react';
import './ListContainer.css';
import {Heading, HeadingLevel} from "baseui/heading";

const ListContainer = (props) => {
    const {match} = props;
    const subsection = match.params.subsection;
    const toTitle = (subsectionName) => subsectionName
        .split('-')
        .map(w => w.charAt(0).toUpperCase() + w.slice(1))
        .join(' ');

    return (
        <div className="ListContainer">
            <HeadingLevel>
                <Heading>{toTitle(subsection)}</Heading>
                {props.children}
            </HeadingLevel>
        </div>
    );
};

ListContainer.propTypes = {};

ListContainer.defaultProps = {};

export default ListContainer;
